/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:40 by jtu               #+#    #+#             */
/*   Updated: 2024/03/26 20:51:15 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*find the path of the command*/
char	*find_path(char *cmd, char **envp)
{
	char		**path;
	char		*path_cmd;
	char		*temp;
	int			i;
	struct stat	buf;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		error_exit(NO_PATH, cmd);
	path = ft_split(*envp + 5, ':');
	i = -1;
	temp = NULL;
	path_cmd = NULL;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		path_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
	}
	ft_freearr(&path);
	if (access(cmd, F_OK) != 0)
		error_exit(CMD_NOT_FOUND, cmd);
	if (stat(cmd, &buf) == 0)
	{
		if (S_ISREG(buf.st_mode))
			error_exit(CMD_NOT_FOUND, cmd);
		else if (S_ISDIR(buf.st_mode))
			error_exit(CMD_NOT_FOUND, cmd);
	}
	else
		error_exit(STAT_FAIL, cmd);
	return (0);
}

void	remove_first_empty_cmd(t_cmd *parsed_cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (parsed_cmd->cmd[i])
	{
		if (parsed_cmd->cmd[0][0] == '\0')
			temp = parsed_cmd->cmd[i];
		i++;
		parsed_cmd->cmd[i - 1] = parsed_cmd->cmd[i];
	}
	parsed_cmd->cmd[i - 1] = NULL;
	free(temp);
}

/*find the command and execute it*/
void	execute_cmd(t_exec *exec, t_cmd parsed_cmd, char **envp)
{
	char		*path;
	int			builtin_status;
	struct stat	buf;

	check_redirections(parsed_cmd);
	if (parsed_cmd.cmd[0][0] == '\0' && parsed_cmd.cmd[1] == NULL)
		exit(0);
	if (parsed_cmd.cmd[0][0] == '\0' && parsed_cmd.cmd[1] != NULL)
		remove_first_empty_cmd(&parsed_cmd);
	builtin_status = run_builtin(exec, parsed_cmd.cmd);
	if (builtin_status != -1)
	{
		exec->exit_code = builtin_status;
		exit(builtin_status);
	}
	if (!parsed_cmd.cmd[0])
		error_exit(CMD_NOT_FOUND, NULL);
	if (!ft_strrchr(parsed_cmd.cmd[0], '/'))
		path = find_path(parsed_cmd.cmd[0], envp);
	else
	{
		if (access(parsed_cmd.cmd[0], F_OK) != 0)
			error_exit(NO_PATH, parsed_cmd.cmd[0]);
		if (access(parsed_cmd.cmd[0], X_OK) != 0)
			error_exit(EXECVE_FAIL, parsed_cmd.cmd[0]);
		if (stat(parsed_cmd.cmd[0], &buf) == 0)
		{
			if (S_ISDIR(buf.st_mode))
				error_exit(IS_DIR, parsed_cmd.cmd[0]);
		}
		else
			error_exit(STAT_FAIL, parsed_cmd.cmd[0]);
		path = parsed_cmd.cmd[0];
	}
	// if (!path)
	// 	error_free_exit(cmd);
	if (execve(path, parsed_cmd.cmd, envp) == -1)
		error_exit(EXECVE_FAIL, path);
}

void	close_pipes(t_exec *exec)
{
	size_t	i;

	i = 0;
	while (i < exec->cmd_count - 1)
	{
		close(exec->pipes[i][RD]);
		close(exec->pipes[i][WR]);
		i++;
	}
}

void	pipe_dup(size_t i, t_exec *exec)
{
	if (i == 0)
	{
		if (dup2(exec->pipes[i][WR], STDOUT_FILENO) < 0)
			error_exit(DUP_FAIL, NULL);
	}
	else if (i == exec->cmd_count - 1)
	{
		if (dup2(exec->pipes[i - 1][RD], STDIN_FILENO) < 0)
			error_exit(DUP_FAIL, NULL);
	}
	else
	{
		if (dup2(exec->pipes[i - 1][RD], STDIN_FILENO) < 0 || dup2(exec->pipes[i][WR], STDOUT_FILENO) < 0)
			error_exit(DUP_FAIL, NULL);
	}
	close_pipes(exec);
}

void	create_pipes(t_exec *exec)
{
	size_t	i;

	exec->pipes = (int **)malloc(sizeof(int *) * (exec->cmd_count - 1));
	if (!exec->pipes)
		error_exit(MALLOC_FAIL, NULL);
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		exec->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!exec->pipes[i])
			error_exit(MALLOC_FAIL, NULL);
		i++;
	}
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		if (pipe(exec->pipes[i]) == -1)
			error_exit(PIPE_FAIL, NULL);
		i++;
	}
}

void	child_process(t_exec *exec)
{
	size_t	i;

	i = 0;
	if (exec->cmd_count > 1)
		create_pipes(exec);
	exec->pid = malloc(sizeof(int) * (exec->cmd_count));
	while (i < exec->cmd_count)
	{
		exec->pid[i] = fork();
		if (exec->pid[i] < 0)
			error_exit(FORK_FAIL, NULL); //
		togglesignal(IGNORE);
		if (exec->pid[i] == 0)
		{
			togglesignal(DEFAULT);
			togglerawmode(0);
			if (exec->cmd_count > 1)
				pipe_dup(i, exec);
			execute_cmd(exec, exec->cmd[i], exec->envp);
		}
		i++;
	}
	close_pipes(exec);
}

/*get the command from parser and create pipes and child process*/
void	executor(t_exec *exec)
{
	size_t	i;
	int		status;

	child_process(exec);
	i = -1;
	while (++i < exec->cmd_count)
		waitpid(exec->pid[i], &status, 0);
	togglesignal(HANDLER);
	exec->exit_code = WEXITSTATUS(status);
}

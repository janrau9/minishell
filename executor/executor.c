/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:40 by jtu               #+#    #+#             */
/*   Updated: 2024/03/14 14:38:45 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_free_exit(char **cmd)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(*cmd, STDERR_FILENO);
	free_arr(cmd);
	exit(127);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*find the path of the command*/
char	*find_path(char *cmd, char **envp)
{
	char	**path;
	char	*path_cmd;
	char	*temp;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
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
	free_arr(path);
	return (0);
}

/*find the command and execute it*/
void	execute_cmd(t_cmd parsed_cmd, char **envp)
{
	char	*path;

	check_redirections(parsed_cmd);
	check_buildins(parsed_cmd.cmd, envp);
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
		path = parsed_cmd.cmd[0];
	}
	// if (!path)
	// 	error_free_exit(cmd);
	if (execve(path, parsed_cmd.cmd, envp) == -1)
		error_exit(EXECVE_FAIL, path);
}

/*get error type, give an error message and exit the project*/
void	error_exit(t_error error, char *s)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (error == CMD_NOT_FOUND)
	{
		ft_putendl_fd("command not found: ", STDERR_FILENO);
		exit(127);
	}
	if (error == NO_PATH)
	{
		ft_putstr_fd("No such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(s, STDERR_FILENO);
		exit(127);
	}
	if (error == EXECVE_FAIL)
	{
		ft_putstr_fd("permission denied: ", STDERR_FILENO);
		if (!s)
			s = "\n";
		ft_putendl_fd(s, STDERR_FILENO);
		exit(126);
	}
	perror(s);
	exit(EXIT_FAILURE);
}

void	dup_child(size_t i, t_exec *exec, int *fd)
{
	if (i == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			error_exit(DUP_FAIL, NULL);
		//close(fd[1]);
	}
	else if (i == exec->cmd_count - 1)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			error_exit(DUP_FAIL, NULL);
		//close(fd[0]);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
			error_exit(DUP_FAIL, NULL);
	}
	close(fd[1]);
	close(fd[0]);
}


/*get the command from parser and create pipes and child process*/
void	executor(t_exec *exec)
{
	int		fd[2];
	size_t	i;
	size_t	j;
	int		status;

	i = 0;
	exec->pid = malloc(sizeof(int) * (exec->cmd_count));
	printf("%zu\n", exec->cmd_count);
	while (i < exec->cmd_count)
	{
		if (exec->cmd[i + 1].cmd != NULL)
			pipe(fd);
		exec->pid[i] = fork();
		if (exec->pid[i] < 0)
			error_exit(FORK_FAIL, NULL); //
		if (exec->pid[i] == 0)
		{
			if (exec->cmd_count > 1)
				dup_child(i, exec, fd);
			execute_cmd(exec->cmd[i], exec->envp);
		}
		if (exec->cmd_count > 1 && i == 0)
			close(fd[1]);
		if (exec->cmd_count > 1 && i == exec->cmd_count - 1)
			close(fd[0]);
		i++;
	}
	j = -1;
	while (++j < i)
		waitpid(exec->pid[j], NULL, 0);
	waitpid(exec->pid[j], &status, 0);
	if (WIFEXITED(status))
		exec->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exec->exit_code = WTERMSIG(status);
}

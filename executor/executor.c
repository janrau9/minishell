/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:40 by jtu               #+#    #+#             */
/*   Updated: 2024/03/12 11:31:45 by jtu              ###   ########.fr       */
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
char	*parse_path(char *cmd, char **envp)
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
void	execute_cmd(char **cmd, char **envp)
{
	char	*path;

	if (!cmd[0])
		error_exit(CMD_NOT_FOUND, NULL);
	if (!ft_strrchr(cmd[0], '/'))
		path = parse_path(cmd[0], envp);
	else
	{
		if (access(cmd[0], F_OK) != 0)
			error_exit(NO_PATH, cmd[0]);
		if (access(cmd[0], X_OK) != 0)
			error_exit(EXECVE_FAIL, cmd[0]);
		path = cmd[0];
	}
	if (!path)
		error_free_exit(cmd);
	if (execve(path, cmd, envp) == -1)
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

void	dup_child(t_cmd *parsed_cmd,int *fd, int fd_in)
{
	if (parsed_cmd && dup2(fd_in, STDIN_FILENO) < 0)
		error_exit(DUP_FAIL, NULL);
	if (parsed_cmd && dup2(fd_in, STDIN_FILENO) < 0)
		error_exit(DUP_FAIL, NULL);
}

/*get the command from parser and create pipes and child process*/
void	executor(t_cmd *parsed_cmd, t_data *data, char **envp)
{
	int		fd[2];
	int		*pid;
	int		i;
	int		j;
	int		fd_in;
	int		status;

	i = 0;
	pid = malloc(sizeof(int) * data->pipe_count);
	while (data->pipe_count--)
	{
		if (parsed_cmd[i + 1].cmd != NULL)
			pipe(fd);
		pid[i] = fork();
		if (pid[i] < 0)
			error_exit(FORK_FAIL, NULL); //
		if (pid[i] == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execute_cmd(parsed_cmd[i].cmd, envp);
			close(fd[1]);
			dup_child(parsed_cmd, fd, fd_in);
		}
		// if (data->here_doc)
		// {
		// 	close(fd[0]);
		// 	fd_in = open();
		// }
		// else
		fd_in = fd[0];
		i++;
	}
	j = 0;
	while (j++ < i)
		waitpid(pid[i], NULL, 0);
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_code = WTERMSIG(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:40 by jtu               #+#    #+#             */
/*   Updated: 2024/03/22 15:34:47 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// #define PROCESS_NUM 1

/*create pipes*/
void	create_pipes(t_exec *exec)
{
	size_t	i;

	exec->pipes = (int **)malloc(sizeof(int *) * (exec->cmd_count - 1));
	if (!exec->pipes)
		error_exit(PIPE_FAIL, NULL);	
	i = 0;
	while (i < exec->cmd_count)
	{
		exec->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!exec->pipes[i])
			error_exit(PIPE_FAIL, NULL);
		i++;
	}
	i = 0;
	while (i < exec->cmd_count)
	{
		if (pipe(exec->pipes[i]) == -1)
		{
			printf("Error with creating pipe\n");
			exit(1);
		}
		i++;
	}
	
}

/*route child pipe and close unused pipes*/
void	route_child_pipe(t_exec *exec, size_t i)
{
	size_t	j;

	if (i == 0)
	{
		j = 0;
		while (j < exec->cmd_count)
		{
			if (i != j)
				close(exec->pipes[j][WR]);
			close(exec->pipes[j][RD]);
			j++;
		}
		dup2(exec->pipes[i][WR], STDOUT_FILENO);
		close(exec->pipes[i][WR]);
	}
	else if (i == exec->cmd_count - 1)
	{
		j = 0;
		while (j < exec->cmd_count)
		{
			if (i - 1 != j)
				close(exec->pipes[j][RD]);
			close(exec->pipes[j][WR]);
			j++;
		}
		dup2(exec->pipes[i - 1][RD], STDIN_FILENO);
		close(exec->pipes[i - 1][RD]);
	}
	else
	{
		j = 0;
		while (j < exec->cmd_count)
		{
			if (i - 1 != j)
				close(exec->pipes[j][RD]);
			if (i != j)
				close(exec->pipes[j][WR]);
			j++;
		}
		dup2(exec->pipes[i - 1][RD], STDIN_FILENO);
		dup2(exec->pipes[i][WR], STDOUT_FILENO);
		close(exec->pipes[i - 1][RD]);
		close(exec->pipes[i][WR]);
	}
}

// void	create_procs(int *pids, int pipes[][2], char **envp, char **cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < PROCESS_NUM)
// 	{
// 		pids[i] = fork();
// 		if (pids[i] == -1)
// 		{
// 			printf("Error with creating process\n");
// 			exit(2);
// 		}
// 		if (pids[i] == 0)
// 		{
// 			route_child_pipe(pipes, i);
// 			dup2(pipes[i][RD], STDIN_FILENO);
// 			dup2(pipes[i + 1][WR], STDOUT_FILENO);
// 			close(pipes[i][RD]);
// 			close(pipes[i + 1][WR]);
// 			execve("/bin/echo", cmd, envp);
// 			exit (0);
// 		}
// 	}
// }

	// int		pids[PROCESS_NUM];
	// int		pipes[PROCESS_NUM][2];
	// int		i;
	// char	*cmd[] = {"/bin/echo", "hello", NULL};
	// create_pipes(pipes);
	// create_procs(pids, pipes, envp, cmd);
	// i = -1;
	// while (++i < PROCESS_NUM + 1)
	// {
	// 	close(pipes[i][RD]);
	// 	close(pipes[i][WR]);
	// }
	// i = -1;
	// while (++i < PROCESS_NUM)
	// 	wait(NULL);

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
void	execute_cmd(t_exec *exec, t_cmd parsed_cmd, char **envp)
{
	char	*path;

	check_redirections(parsed_cmd);
	if (check_builtins(exec, parsed_cmd.cmd))
	 	return ;
	(void)exec;
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
	ft_putstr_fd("jjsh-1.0: ", STDERR_FILENO);
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

// void	dup_child(size_t i, t_exec *exec, int *fd)
// {
// 	if (i == 0)
// 	{
// 		if (dup2(fd[1], STDOUT_FILENO) < 0)
// 			error_exit(DUP_FAIL, NULL);
// 		//close(fd[1]);
// 	}
// 	else if (i == exec->cmd_count - 1)
// 	{
// 		if (dup2(fd[0], STDIN_FILENO) < 0)
// 			error_exit(DUP_FAIL, NULL);
// 		//close(fd[0]);
// 	}
// 	else
// 	{
// 		if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
// 			error_exit(DUP_FAIL, NULL);
// 	}
// 	close(fd[1]);
// 	close(fd[0]);
// }

void	child_process(t_exec *exec)
{
	size_t	i;


	i = 0;
	create_pipes(exec);
	exec->pid = malloc(sizeof(int) * (exec->cmd_count));
	while (i < exec->cmd_count)
	{
		exec->pid[i] = fork();
		if (exec->pid[i] < 0)
			error_exit(FORK_FAIL, NULL); //
		if (exec->pid[i] == 0)
		{
			route_child_pipe(exec, i);
			execute_cmd(exec, exec->cmd[i], exec->envp);
		}
		i++;
	}
	i = -1;
	while (++i < exec->cmd_count)
	{
		close(exec->pipes[i][RD]);
		close(exec->pipes[i][WR]);
	}
}


/*get the command from parser and create pipes and child process*/
void	executor(t_exec *exec)
{
	size_t	i;
	int		status;

	// printf("%s\n", exec->cmd[0].cmd[0]);
	// if (!ft_strncmp(exec->cmd[0].cmd[0], "unset", 6))
	// 	ft_unset(exec);
	// printf("%zu\n", exec->cmd_count); //
	
	child_process(exec);
	i = -1;
	while (++i < exec->cmd_count)
		waitpid(exec->pid[i], &status, 0);
	exec->exit_code = WEXITSTATUS(status);
}

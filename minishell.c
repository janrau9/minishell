/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:41:38 by jberay            #+#    #+#             */
/*   Updated: 2024/03/13 13:49:06 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #define PROCESS_NUM 1
// #define RD 0
// #define WR 1

// /*create pipes*/
// void	create_pipes(int pipes[][2])
// {
// 	int	i;

// 	i = -1;
// 	while (++i < PROCESS_NUM + 1)
// 	{
// 		if (pipe(pipes[i]) == -1)
// 		{
// 			printf("Error with creating pipe\n");
// 			exit(1);
// 		}
// 	}
// }

// /*route child pipe and close unused pipes*/
// void	route_child_pipe(int pipes[][2], int i)
// {
// 	int	j;

// 	if (i == 0)
// 	{
// 		j = -1;
// 		while (++j < PROCESS_NUM + 1)
// 		{
// 			if (i != j)
// 				close(pipes[j][RD]);
// 			close(pipes[j][WR]);
// 		}
// 	}
// 	else
// 	{
// 		j = -1;
// 		while (++j < PROCESS_NUM + 1)
// 		{
// 			if (i != j)
// 				close(pipes[j][RD]);
// 			if (i - 1 != j)
// 				close(pipes[j][WR]);
// 		}
// 	}
// }

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
// // loooping through the pipes, forks, and closing the read and write ends

// int	main(int argc, char **argv, char **envp)
// {

// 	int		pids[PROCESS_NUM];
// 	int		pipes[PROCESS_NUM][2];
// 	int		i;
// 	char	*cmd[] = {"/bin/echo", "hello", NULL};
// 	create_pipes(pipes);
// 	create_procs(pids, pipes, envp, cmd);
// 	i = -1;
// 	while (++i < PROCESS_NUM + 1)
// 	{
// 		close(pipes[i][RD]);
// 		close(pipes[i][WR]);
// 	}
// 	i = -1;
// 	while (++i < PROCESS_NUM)
// 		wait(NULL);
// 	return (0);
// }

// parsing part

void	print_cmd(t_cmd **cmd_ptr)
{
	size_t	i;
	size_t	j;
	t_cmd	*cmd;

	cmd = *cmd_ptr;

	j = 0;
	i = 0;
	while (cmd[j].cmd != NULL)
	{
		printf("\nsimple command[%zu]\n", j);
		i = 0;
		while (cmd[j].cmd[i] != 0)
		{
			printf("cmd[%zu]:%s\n", i, cmd[j].cmd[i]);
			i++;
		}
		printf("cmd[%zu]:%s\n", i, cmd[j].cmd[i]);
		i = 0;
		while (cmd[j].redir[i] != 0)
		{
			printf("redir[%zu]:%s\n", i, cmd[j].redir[i]);
			i++;
		}
		printf("redir[%zu]:%s\n\n", i, cmd[j].redir[i]);
		j++;
	}
}

void	print_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("env[%zu]:%s\n", i, array[i]);
		i++;
	}
}

void	re_promt(char **read_line_add)
{
	char	*read_line;
	char	*tmp;
	char	*add_space;

	read_line = *read_line_add;
	readline("> ");
	add_space = read_line;
	tmp = ft_strjoin(add_space, " ");
	if (!tmp)
	{
		free(add_space);
		exit (2);
	}
	free(add_space);
	read_line = ft_strjoin(tmp, rl_line_buffer);
	if (!read_line)
	{
		free(tmp);
		exit (2);
	}
	free(tmp);
	add_history(read_line);
	*read_line_add = read_line;
}

int	check_command_after_pipe(t_data *data)
{
	size_t	i;
	int		cmd_flag;
	char	*read_line;

	read_line = data->read_line;
	cmd_flag = 0;
	while (cmd_flag == 0)
	{
		if (tokenizer(read_line, &data->token))
			return (1);
		i = ft_strlen(read_line);
		while (read_line[i] != '|' && i > 0)
		{
			--i;
			if (read_line[i] != ' ' && read_line[i] != '|')
				cmd_flag = 1;
		}
		if (cmd_flag == 0)
			re_promt(&read_line);
	}
	return (0);
}

void	create_heredoc_name(char **heredoc_name, int child)
{
	char	*tmp;

	tmp = ft_itoa(child);
	if (!tmp)
		exit (2);
	*heredoc_name = ft_strjoin("/tmp/heredoc", tmp);
	if (!*heredoc_name)
	{
		free(tmp);
		exit (2);
	}
	free(tmp);
	unlink(*heredoc_name);
}

void	heredoc(t_cmd **cmd_add)
{
	t_cmd	*cmd;
	size_t	i;
	size_t	j;
	int		fd;
	char	*heredoc;
	char	*heredoc_name;
	char	*tmp;

	cmd = *cmd_add;
	i = 0;
	while (cmd[i].redir != NULL)
	{
		j = 0;
		while (cmd[i].redir[j] != NULL)
		{
			if (ft_strncmp(cmd[i].redir[j], "<<", 2) == 0)
			{
				create_heredoc_name(&heredoc_name, i);
				fd = open(heredoc_name, O_TRUNC | O_CREAT | O_RDWR, 0666);
				while (1)
				{
					heredoc = readline("heredoc> ");
					if (ft_strncmp(heredoc, cmd[i].redir[j + 1], ft_strlen(heredoc)) == 0)
						break ;
					write(fd, heredoc, ft_strlen(heredoc));
					write(fd, "\n", 1);
					free(heredoc);
				}
				tmp = cmd[i].redir[j + 1];
				cmd[i].redir[j + 1] = heredoc_name;
				free(tmp);
				print_cmd(&cmd);
				close(fd);
				// unlink("/tmp/heredoc.txt");
			}
			j++;
		}
		i++;
	}
	*cmd_add = cmd;
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_redisplay();
	}
}

void enablerawmode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_arrcpy(char ***dst_add, char **src)
{
	size_t	src_size;
	size_t	i;
	char	**dst;

	dst = *dst_add;
	src_size = ft_arrlen(src);
	i = 0;
	while (i < src_size)
	{
		dst[i] = src[i];
		i++;
	}
	*dst_add = dst;
}

void	ft_arrdup(char ***dst_add, char **src)
{
	size_t	src_size;
	size_t	i;
	char	**dst;

	if (!src)
		return ;
	src_size = ft_arrlen(src);
	dst = ft_calloc(src_size + 1, sizeof(char *));
	if (!dst)
		exit (2);
	i = 0;
	while (i < src_size)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			exit (2);
		i++;
	}
	dst[i] = NULL;
	*dst_add = dst;
}
void	ft_freearr(char ***array)
{
	size_t	i;
	char	**tmp;

	i = 0;
	tmp = *array;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	*array = NULL;
}

void	ft_freestruct(t_cmd **cmd)
{
	t_cmd	*tmp;
	size_t	i;

	tmp = *cmd;
	i = 0;
	while (tmp[i].cmd != NULL)
	{
		ft_freearr(&tmp[i].cmd);
		ft_freearr(&tmp[i].redir);
		i++;
	}
	free(tmp);
}
int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_cmd	*cmd;
	t_exec	exec;

	(void)argc;
	(void)argv;
	(void)envp;
	enablerawmode();
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	while (1)
	{
		data.read_line = readline ("jjsh-1.0$ ");
		if (!data.read_line)
		{
			printf("Exiting minishell\n");
			exit (0);
		}
		if (!ft_strncmp(data.read_line, "exit", 5))
		{
			free(data.read_line);
			printf("Exiting minishell\n");
			exit (0);
		}
		if (*data.read_line != '\0')
		{
			add_history(data.read_line);
			if (!check_command_after_pipe(&data))
			{
				parse(&cmd, &data);
				exec.cmd = cmd;
				exec.cmd_count = data.pipe_count + 1;
				heredoc(&exec.cmd);
				// exec.envp = NULL;
				// ft_arrdup(&exec.envp, envp);
				// builtin(&exec);
				print_cmd(&cmd);
				// print_array(exec.envp);
				// ft_freearr(&exec.envp);
				// ft_freestruct(&cmd);
			}
		}
		free(data.read_line);
		free(data.token);
	}
	return (0);
}

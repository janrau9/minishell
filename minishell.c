/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:41:38 by jberay            #+#    #+#             */
/*   Updated: 2024/03/12 11:15:28 by jtu              ###   ########.fr       */
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
		printf("Printing cmd array\n");
		i = 0;
		while (cmd[j].cmd[i] != 0)
		{
			printf("scmd[%zu] cmd[%zu]:%s\n", j, i, cmd[j].cmd[i]);
			i++;
		}
		printf("scmd[%zu] cmd[%zu]:%s\n", j, i, cmd[j].cmd[i]);
		i = 0;
		while (cmd[j].redir[i] != 0)
		{
			printf("sredir[%zu] redir[%zu]:%s\n", j, i, cmd[j].redir[i]);
			i++;
		}
		printf("sredir[%zu] redir[%zu]:%s\n", j, i, cmd[j].redir[i]);
		j++;
	}
}

void	check_command_after_pipe(t_data *data, char **read_line_add)
{
	char	*tmp;
	char	*add_space;
	size_t	i;
	int		cmd_flag;
	char	*read_line;

	read_line = *read_line_add;
	cmd_flag = 0;
	while (cmd_flag == 0)
	{
		if (tokenizer(read_line, &data->token))
		{
			token_print(data->token);
			printf("error tokenizing\n");
			exit(1);
		}
		i = ft_strlen(read_line);
		while (read_line[i] != '|' && i > 0)
		{
			--i;
			if (read_line[i] != ' ' && read_line[i] != '|')
				cmd_flag = 1;
		}
		if (cmd_flag == 0)
		{
			readline("> ");
			add_space = read_line;
			tmp = ft_strjoin(add_space, " ");
			free(add_space);
			read_line = ft_strjoin(tmp, rl_line_buffer);
			free(tmp);
			add_history(read_line);
			*read_line_add = read_line;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*read_line;

	t_data	data;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	(void)envp;

	while (1)
	{
		read_line = readline ("janrau:~$");
		if (ft_strncmp(read_line, "exit", 4) == 0)
		{
			free(read_line);
			printf("Exiting minishell\n");
			exit (0);
		}
		add_history(read_line);
		check_command_after_pipe(&data, &read_line);
		// rl_replace_line("janrau", 0);
		// rl_redisplay();

		// printf("result read_line: %s\n", read_line);



		// printf("replace %s\n", rl_line_buffer);
		// printf("replace %s\n", read_line);

		// printf("redisplay %s\n", rl_line_buffer);
		// printf("redisplay %s\n", read_line);


		// tokenizer(read_line, &data.token);
		//token_print(data.token);
		parse(&cmd, &data, read_line);
		executor(cmd, &data, envp);
		print_cmd(&cmd);

		// free(read_line);
		// free(data.token);
	}
	return (0);
}
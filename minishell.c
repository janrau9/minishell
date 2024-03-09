/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:41:38 by jberay            #+#    #+#             */
/*   Updated: 2024/03/08 12:52:08 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "char_iter.h"
#include "token.h"

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

/*remove consecutive quotes*/

int	main(int argc, char **argv, char **envp)
{
	char	*read_line;
	t_cmd	cmd;
	t_data	data;
	t_list	*cmds_lst;

	(void)argc;
	(void)argv;
	(void)envp;
	cmds_lst = NULL;
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
		tokenizer(read_line, &data.token);
		//token_print(data.token);
		parse(&cmds_lst, &cmd, &data, read_line);

		while (cmds_lst)
		{
			printf("her	\n");
			cmd = *(t_cmd *)cmds_lst->content;
			size_t size = 0;
			while (cmd.cmd[size] != 0)
			{
				printf("cmd[%zu]:%s\n", size, cmd.cmd[size]);
				size++;
			}
			printf("cmd[%zu]:%s\n", size, cmd.cmd[size]);

			size = 0;
			while (cmd.redir[size] != 0)
			{
				printf("redir[%zu]:%s\n", size, cmd.redir[size]);
				size++;
			}
			printf("redir[%zu]:%s\n", size, cmd.redir[size]);
			cmds_lst = cmds_lst->next;
		}

	/* 	size_t size = 0;
		while (cmd.cmd[size] != 0)
		{
			printf("cmd[%zu]:%s\n", size, cmd.cmd[size]);
			size++;
		}
		printf("cmd[%zu]:%s\n", size, cmd.cmd[size]);

		size = 0;
		while (cmd.redir[size] != 0)
		{
			printf("redir[%zu]:%s\n", size, cmd.redir[size]);
			size++;
		}
		printf("redir[%zu]:%s\n", size, cmd.redir[size]); */
		//token_print(cmds.token);
		free(read_line);
		free(data.token);
	}
	return (0);
}
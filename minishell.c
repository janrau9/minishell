/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:41:38 by jberay            #+#    #+#             */
/*   Updated: 2024/03/14 14:53:18 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("Here %s\n", rl_prompt);
		printf("buffer %s\n", rl_line_buffer);
		if (ft_strncmp(rl_prompt, "heredoc> ", 9) == 0)
			rl_redisplay();
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

void	togglesignal(int mode)
{
	if (mode == 1)
	{
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}

}

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

int	re_promt(t_data *data)
{
	char	*read_line_new;
	char	*rd_space;

	read_line_new = readline("> ");
	if (!*read_line_new)
		return (0);
	if (!read_line_new)
		return (UNEXPECTED_EOF);
	rd_space = ft_strjoin(data->read_line, " ");
	if (!rd_space)
		return (MALLOC_ERROR);
	free(data->read_line);
	ft_strjoin_custom(&data->read_line, rd_space, read_line_new);
	if (!data->read_line)
	{
		free(rd_space);
		free(read_line_new);
		return (MALLOC_ERROR);
	}
	add_history(data->read_line);
	return (0);
}

int	check_command_after_pipe(t_data *data)
{
	size_t	i;
	int		cmd_flag;
	int		err_return;

	cmd_flag = 0;
	while (cmd_flag == 0)
	{
		err_return = tokenizer(data);
		if (err_return)
			return (err_return);
		i = ft_strlen(data->read_line);
		while (data->read_line[--i] != '|' && i > 0)
		{
			if (data->read_line[i] != ' ' && data->read_line[i] != '|')
				cmd_flag = 1;
		}
		if (cmd_flag == 0)
		{
			err_return = re_promt(data);
			if (err_return)
				return (err_return);
			free(data->token);
		}
	}
	return (0);
}

void	create_heredoc_name(t_data *data, char **heredoc_name, int child)
{
	char	*tmp;

	tmp = ft_itoa(child);
	if (!tmp)
		ft_error(data, "malloc error", MALLOC_ERROR);
	*heredoc_name = ft_strjoin("/tmp/heredoc", tmp);
	if (!*heredoc_name)
	{
		free(tmp);
		ft_error(data, "malloc error", MALLOC_ERROR);
	}
	free(tmp);
	unlink(*heredoc_name);
}
// int	write_to_heredoc(t_data *data, int fd, char *heredoc)
// {
// 	write(fd, heredoc, ft_strlen(heredoc));
// 	write(fd, "\n", 1);
// 	free(heredoc);
// 	return (0);
// }

void	heredoc(t_data *data)
{
	size_t	scmd_iter;
	size_t	iter;
	int		fd;
	char	*heredoc;
	char	*tmp;
	char	*heredoc_name;

	scmd_iter = 0;
	while (data->exec.cmd[scmd_iter].redir != NULL)
	{
		iter = 0;
		while (data->exec.cmd[scmd_iter].redir[iter] != NULL)
		{
			if (ft_strncmp(data->exec.cmd[scmd_iter].redir[iter], "<<", 2) == 0)
			{
				create_heredoc_name(data, &heredoc_name, scmd_iter);
				fd = open(heredoc_name, O_TRUNC | O_CREAT | O_RDWR, 0666);
				while (1)
				{
					heredoc = readline("heredoc> ");
					if (!heredoc)
					{
						close(fd);
						return ;
					}
					if (*heredoc == '\0')
						printf("iamhere %s\n", rl_line_buffer);
					if (ft_strncmp(heredoc, data->exec.cmd[scmd_iter].redir[iter + 1], \
					ft_strlen(data->exec.cmd[scmd_iter].redir[iter + 1])) == 0)
						break ;
					write(fd, heredoc, ft_strlen(heredoc));
					write(fd, "\n", 1);
					free(heredoc);
				}
				tmp = data->exec.cmd[scmd_iter].redir[iter + 1];
				data->exec.cmd[scmd_iter].redir[iter + 1] = heredoc_name;
				free(tmp);
				close(fd);
				// unlink("/tmp/heredoc.txt");
			}
			iter++;
		}
		scmd_iter++;
	}
}


void enablerawmode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
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
void	initialize_data(t_data *data, char **envp)
{
	data->read_line = NULL;
	data->token = NULL;
	data->token_iter = 0;
	data->cmds_iter = 0;
	data->redir_iter = 0;
	data->exec.pipe_count = 0;
	data->exec.cmd = NULL;
	data->exec.envp = NULL;
	data->exec.exit_code = ft_arrdup(&data->exec.envp, envp);
}



/*
** Malloced
** 1. data->read_line
** 2. data->token
** 3. data->exec.cmd
** 4. data->exec.envp
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	enablerawmode();
	togglesignal(1);
	initialize_data(&data, envp);
	while (data.exec.exit_code >= 0)
	{
		data.read_line = readline ("jjsh-1.0$ ");
		if (!data.read_line || !ft_strncmp(data.read_line, "exit", 5))
		{
			free(data.read_line);
			printf("Exiting minishell\n");
			exit (0);
		}
		if (*data.read_line != '\0')
		{
			add_history(data.read_line);
			data.shell_status = check_command_after_pipe(&data);
			if (data.shell_status == 0)
			{
				printf("read_line:%s\n", rl_line_buffer);
				parse(&data);
				heredoc(&data);
				//builtin(&data);
				print_cmd(&data.exec.cmd);
				// print_array(data.exec.envp);
				// ft_freestruct(&data.exec.cmd);
				// token_print(data.token);
				executor(&data.exec);
				free(data.token);
				free(data.read_line);
				
			}
		}
	}
	return (0);
}

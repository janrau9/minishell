/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:06:14 by jberay            #+#    #+#             */
/*   Updated: 2024/03/15 12:12:21 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_heredoc_name(t_data *data, char **heredoc_name, int child)
{
	char	*tmp;

	tmp = ft_itoa(child);
	if (!tmp)
		ft_error(data, "malloc error", MALLOC_ERROR);
	*heredoc_name = ft_strjoin("/tmp/heredoc_", tmp);
	if (!*heredoc_name)
	{
		free(tmp);
		ft_error(data, "malloc error", MALLOC_ERROR);
	}
	free(tmp);
	unlink(*heredoc_name);
}

static void	write_to_heredoc(t_data *data, int fd, char *delimiter, char *heredoc_name)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("heredoc> ");
		if (!heredoc)
		{
			close(fd);
			unlink(heredoc_name);
			ft_error(data, "unexpected eof", 130);
			break ;
		}
		if (ft_strncmp(heredoc, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(heredoc);
			break ;
		}
		write(fd, heredoc, ft_strlen(heredoc));
		write(fd, "\n", 1);
		free(heredoc);
	}
}

/*remember to unlink heredoc file after minishell use*/
void	run_heredoc(t_data *data)
{
	size_t	child_iter;
	size_t	iter;
	int		fd;
	char	*delimiter;
	char	*heredoc_name;

	child_iter = -1;
	while (data->exec.cmd[++child_iter].redir != NULL)
	{
		iter = -1;
		while (data->exec.cmd[child_iter].redir[++iter] != NULL)
		{
			if (!ft_strncmp(data->exec.cmd[child_iter].redir[iter], "<<", 2))
			{
				create_heredoc_name(data, &heredoc_name, child_iter);
				fd = open(heredoc_name, O_TRUNC | O_CREAT | O_RDWR, 0644);
				delimiter = data->exec.cmd[child_iter].redir[iter + 1];
				write_to_heredoc(data, fd, delimiter, heredoc_name);
				data->exec.cmd[child_iter].redir[iter + 1] = heredoc_name;
				free(delimiter);
				close(fd);
			}
		}
	}
}

void	heredoc(t_data *data)
{
	size_t	t_iter;
	int		status;
	int		heredoc_child;

	t_iter = -1;
	while (data->token[++t_iter].type != EOL_TOKEN)
	{
		if (data->token[t_iter].type == REDIR_HEREDOC_TOKEN)
		{
			heredoc_child = fork();
			if (heredoc_child == -1)
				ft_error(data, "fork error", FORK_ERROR);
			if (heredoc_child == 0)
			{
				togglesignal(0);
				run_heredoc(data);
				ft_freeall(data);
				togglesignal(1);
				exit(0);
			}
			waitpid(heredoc_child, &status, 0);
			if (status == SIGINT)
				printf("reprompt\n");
			if (status == SIGQUIT)
				printf("unexpected eof\n");
		}
	}

}
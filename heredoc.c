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
	*heredoc_name = ft_strjoin("/tmp/heredoc", tmp);
	if (!*heredoc_name)
	{
		free(tmp);
		ft_error(data, "malloc error", MALLOC_ERROR);
	}
	free(tmp);
	unlink(*heredoc_name);
}

static void	write_to_heredoc(t_data *data, int fd, \
size_t child_iter, size_t iter)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("heredoc> ");
		if (!heredoc)
		{
			close(fd);
			break ;
		}
		if (ft_strncmp(heredoc, data->exec.cmd[child_iter].redir[iter + 1], \
		ft_strlen(data->exec.cmd[child_iter].redir[iter + 1])) == 0)
			break ;
		write(fd, heredoc, ft_strlen(heredoc));
		write(fd, "\n", 1);
		free(heredoc);
	}
}

/*remember to unlink heredoc file after minishell use*/
void	heredoc(t_data *data)
{
	size_t	child_iter;
	size_t	iter;
	int		fd;
	char	*tmp;
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
				fd = open(heredoc_name, O_TRUNC | O_CREAT | O_RDWR, 0666);
				write_to_heredoc(data, fd, child_iter, iter);
				tmp = data->exec.cmd[child_iter].redir[iter + 1];
				data->exec.cmd[child_iter].redir[iter + 1] = heredoc_name;
				free(tmp);
				close(fd);
			}
		}
	}
}
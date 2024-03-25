/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:06:14 by jberay            #+#    #+#             */
/*   Updated: 2024/03/25 10:18:41 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_heredoc(t_exec *exec, int fd, char *delimiter, int is_expand)
{
	int		heredoc_child;
	int		status;

	g_prompt = 3;
	heredoc_child = fork();
	if (heredoc_child == -1)
		ft_error(exec, "fork error", FORK_ERROR);
	if (heredoc_child == 0)
	{
		togglesignal(0);
		write_to_heredoc(exec, fd, delimiter, is_expand);
		togglesignal(1);
		exit(0);
	}
	waitpid(heredoc_child, &status, 0);
	g_prompt = 0;
	if (status == SIGINT)
	{
		printf("\n");
		return (1);
	}
	return (0);
}

static void	create_heredoc_name(t_exec *exec, char **heredoc_name, int id)
{
	char	*tmp;

	tmp = ft_itoa(id);
	if (!tmp)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	*heredoc_name = ft_strjoin(".heredoc_", tmp);
	if (!*heredoc_name)
	{
		free(tmp);
		ft_error(exec, "malloc error", MALLOC_ERROR);
	}
	free(tmp);
	unlink(*heredoc_name);
}

/*remember to unlink heredoc file after minishell use*/
int	heredoc(t_exec *exec, char **dst, t_iterator *iter, bool is_expand)
{
	int		fd;
	char	*heredoc_name;
	char	*delimiter;

	create_heredoc_name(exec, &heredoc_name, iter->redir_iter);
	fd = open(heredoc_name, O_TRUNC | O_CREAT | O_RDWR, 0644);
	delimiter = ft_strdup(exec->cmd->redir[iter->redir_iter]);
	if (!delimiter)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	if (run_heredoc(exec, fd, delimiter, is_expand))
		return (1);
	*dst = heredoc_name;
	close(fd);
	return (0);
}

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

void	parse_heredoc(t_exec *exec, char **dst, t_iterator *iter, bool is_expand)
{
	char	*str[3];

	str[0] = ft_strdup("");
	if (!str[0])
		ft_error(exec, "malloc error", MALLOC_ERROR);
	while (exec->token[iter->token_iter].type != EOL_TOKEN)
	{
		str[2] = str[0];
		if (exec->token[iter->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(exec, &str[1], iter, is_expand);
		else
		{
			if (exec->token[iter->token_iter].type == OPEN_DQUOTE_TOKEN)
			{
				exec->token[iter->token_iter].location.start--;
				exec->token[iter->token_iter].location.len++;
			}
			if (exec->token[iter->token_iter].type == CLOSE_DQUOTE_TOKEN)
				exec->token[iter->token_iter].location.len++;
			if (exec->token[iter->token_iter].type == SQUOTE_TOKEN)
			{
				exec->token[iter->token_iter].location.start--;
				exec->token[iter->token_iter].location.len++;
				exec->token[iter->token_iter].location.len++;
			}
			parse_string(exec, &str[1], iter);
		}
		ft_strjoin_custom(&str[0], str[2], str[1]);
		if (!str[0])
			ft_error(exec, "malloc error", MALLOC_ERROR);
	}
	*dst = str[0];
}

static void	write_to_heredoc(t_exec *exec, int fd, char *delimiter, int is_expand)
{
	t_iterator	iter;
	char		*heredoc;

	while (1)
	{
		ft_freeall_n_envp(exec);
		initialize_exec(exec);
		iter.token_iter = 0;
		exec->read_line = readline("heredoc> ");
		if (!exec->read_line)
		{
			close(fd);
			printf("unexpected eof\n");
			break ;
		}
		if (ft_strncmp(exec->read_line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			printf("break\n");
			ft_freeall(exec);
			return ;
		}
		tokenizer(exec);
		printf("readline = %s\n", exec->read_line);
		parse_heredoc(exec, &heredoc, &iter, is_expand);
		printf("heredoc = %s\n", heredoc);
		write(fd, heredoc, ft_strlen(heredoc));
		write(fd, "\n", 1);
		free(heredoc);
	}
}

void	run_heredoc(t_exec *exec, int fd, char *delimiter, int is_expand)
{
	int		heredoc_child;
	int		status;

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
	if (status == SIGINT)
		printf("reprompt\n");
	if (status == SIGQUIT)
		printf("unexpected eof\n");
}

static void	create_heredoc_name(t_exec *exec, char **heredoc_name, int id)
{
	char	*tmp;

	tmp = ft_itoa(id);
	if (!tmp)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	*heredoc_name = ft_strjoin("/tmp/heredoc_", tmp);
	if (!*heredoc_name)
	{
		free(tmp);
		ft_error(exec, "malloc error", MALLOC_ERROR);
	}
	free(tmp);
	unlink(*heredoc_name);
}

/*remember to unlink heredoc file after minishell use*/
void	heredoc(t_exec *exec, char **dst, t_iterator *iter, bool is_expand)
{
	int		fd;
	char	*heredoc_name;
	char	*delimiter;

	create_heredoc_name(exec, &heredoc_name, iter->redir_iter);
	fd = open(heredoc_name, O_TRUNC | O_CREAT | O_RDWR, 0644);
	delimiter = ft_strdup(exec->cmd->redir[iter->redir_iter]);
	if (!delimiter)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	run_heredoc(exec, fd, delimiter, is_expand);
	*dst = heredoc_name;
	//write_to_heredoc(exec, fd, delimiter, heredoc_name);
	close(fd);
}

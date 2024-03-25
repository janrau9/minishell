/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:54:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/25 15:17:55 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_prompt(t_exec *exec, char *read_line_new)
{
	char	*rd_space;

	rd_space = ft_strjoin(exec->read_line, " ");
	if (!rd_space)
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	free(exec->read_line);
	ft_strjoin_custom(&exec->read_line, rd_space, read_line_new);
	if (!exec->read_line)
	{
		free(rd_space);
		free(read_line_new);
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	}
	add_history(exec->read_line);
}

static int	re_promt(t_exec *exec)
{
	char	*read_line_new;
	int		fd_stdin;

	g_prompt = 2;
	fd_stdin = dup(STDIN_FILENO);
	read_line_new = readline("> ");
	if (!read_line_new && g_prompt == 1)
	{
		dup2(fd_stdin, STDIN_FILENO);
		return (SYNTAX_ERROR);
	}
	if (!read_line_new)
	{
		g_prompt = 1;
		ft_putendl_fd("jjsh-1.0: syntax error: unexpected end of file", 2);
		return (SYNTAX_ERROR);
	}
	if (!*read_line_new)
		return (0);
	join_prompt(exec, read_line_new);
	return (0);
}

int	check_command(t_exec *exec)
{
	size_t	i;
	int		cmd_flag;

	cmd_flag = 0;
	while (cmd_flag == 0)
	{
		i = ft_strlen(exec->read_line);
		if (i == 1)
			break ;
		while (exec->read_line[--i] != '|' && i > 0)
		{
			if (exec->read_line[i] != ' ' && exec->read_line[i] != '|')
				cmd_flag = 1;
		}
		if (cmd_flag == 0)
		{
			if (re_promt(exec))
				return (SYNTAX_ERROR);
		}
	}
	tokenizer(exec);
	if (check_syntax(exec->token))
		return (SYNTAX_ERROR);
	return (0);
}

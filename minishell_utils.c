/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:54:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/25 13:04:18 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	join_prompt(t_exec *exec, char *old)
// {
// 	char	*rd_space;

// 	rd_space = ft_strjoin(exec->read_line, " ");
// 	if (!rd_space)
// 		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
// 	free(exec->read_line);
// 	ft_strjoin_custom(&exec->read_line, rd_space, read_line_new);
// 	if (!exec->read_line)
// 	{
// 		free(rd_space);
// 		free(read_line_new);
// 		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
// 	}
// 	add_history(exec->read_line);
// }

static void	join_prompt(t_exec *exec, char *old)
{
	char	*rd_space;
	char	*read_line_new;
	char	*tmp;

	rd_space = ft_strjoin(old, " ");
	tmp = exec->read_line;
	if (!rd_space)
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	printf("new: %s\n", exec->read_line);
	printf("rd_space: %s\n", rd_space);
	ft_strjoin_custom(&read_line_new, rd_space, tmp);
	if (!read_line_new)
	{
		free(rd_space);
		free(tmp);
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	}
	printf("aexec->read_line: %s\n", read_line_new);
	exec->read_line = read_line_new;
	add_history(exec->read_line);
}

// static int	re_promt(t_exec *exec)
// {
// 	char	*read_line_new;
// 	int		fd_stdin;

// 	g_prompt = 2;
// 	fd_stdin = dup(STDIN_FILENO);
// 	read_line_new = readline("> ");
// 	if (!read_line_new && g_prompt == 1)
// 	{
// 		dup2(fd_stdin, STDIN_FILENO);
// 		return (SYNTAX_ERROR);
// 	}
// 	if (!read_line_new)
// 	{
// 		g_prompt = 1;
// 		ft_putendl_fd("jjsh-1.0: syntax error: unexpected end of file", 2);
// 		return (SYNTAX_ERROR);
// 	}
// 	if (!*read_line_new)
// 		return (0);
// 	join_prompt(exec, read_line_new);
// 	return (0);
// }

int	check_command(t_exec *exec)
{
	size_t	i;
	int		cmd_flag;
	char	*old;
	char	*name;
	int		join;

	cmd_flag = 0;
	join = 0;
	name = "jjsh-1.0$ ";
	while (cmd_flag == 0)
	{
		exec->read_line = readline (name);
		if (!exec->read_line)
		{
			ft_freeall(exec);
			exit (0);
		}
		if (*exec->read_line != '\0')
		{
			tokenizer(exec);
			if (check_syntax(exec->token))
				return (SYNTAX_ERROR);
			i = ft_strlen(exec->read_line);
			if (i == 1)
				return (0);
			while (exec->read_line[--i] != '|' && i > 0)
			{
				if (exec->read_line[i] != ' ' && exec->read_line[i] != '|')
				{
					cmd_flag = 1;
					if (join > 0)
						join_prompt(exec, old);
				}
			}
			if (cmd_flag == 0)
			{
				name = "> ";
				if (join > 0)
					join_prompt(exec, old);
				old = exec->read_line;
				join++;
				printf("old: %s\n", old);
				printf("read_line: %s\n", exec->read_line);
			}
			add_history(exec->read_line);
		}
	}
	return (0);
}

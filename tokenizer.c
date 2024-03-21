/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:10:55 by jberay            #+#    #+#             */
/*   Updated: 2024/03/14 09:27:40 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer_loop(t_token *token, t_char_iter *iter, int *d_flag)
{
	if (iter->start[0] == '<' && *d_flag % 2 == 0)
		take_redir_in(iter, token);
	else if (iter->start[0] == '>' && *d_flag % 2 == 0)
		take_redir_out(iter, token);
	else if (iter->start[0] == '\'' && *d_flag % 2 == 0)
		take_squote(iter, token);
	else if (iter->start[0] == ' ' && *d_flag % 2 == 0)
		take_space(iter, token);
	else if (iter->start[0] == '"')
		take_dquote(iter, token, d_flag);
	else if (iter->start[0] == '$')
		take_dollar(iter, token, d_flag);
	else if (iter->start[0] == '|' && *d_flag % 2 == 0)
		take_pipe(iter, token);
	else
		take_string(iter, token, d_flag);
}

/*
	** This function takes a string and converts it to array of tokens
*/
int	tokenizer(t_exec *exec)
{
	t_char_iter		iter;
	t_token			*token;
	int				d_flag;
	size_t			i;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (MALLOC_ERROR);
	iter = char_iter_constructor(exec->read_line, ft_strlen(exec->read_line));
	i = 0;
	d_flag = 0;
	while (char_iter_cursor(&iter) != iter.end)
	{
		tokenizer_loop(&token[i], &iter, &d_flag);
		i++;
		if (ft_realloc(&token, i + 1))
			return (MALLOC_ERROR);
	}
	take_eol(&iter, &token[i]);
	exec->token = token;
	return (0);
}

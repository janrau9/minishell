/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:19:37 by jberay            #+#    #+#             */
/*   Updated: 2024/03/12 10:20:15 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_eol(t_char_iter *iter, t_token *token)
{
	token->type = EOL_TOKEN;
	token->location.start = char_iter_cursor(iter);
	token->location.len = 0;
}

void	take_pipe(t_char_iter *iter, t_token *token)
{
	token->type = PIPE_TOKEN;
	token->location.start = char_iter_cursor(iter);
	token->location.len = 1;
	char_iter_next(iter);
}

void	take_error(t_char_iter *iter, t_token *token, int d_flag)
{
	token->type = ERROR_TOKEN;
	token->location.start = char_iter_cursor(iter);
	if (d_flag % 2 == 1)
	{
		token->location.start = char_find_dq(iter);
		*iter = char_iter_constructor(token->location.start, \
		ft_strlen(token->location.start));
	}
	printf("error token %s\n", token->location.start);
	token->location.len = 0;
	while (char_iter_cursor(iter) != iter->end)
	{
		char_iter_next(iter);
		token->location.len++;
	}
}
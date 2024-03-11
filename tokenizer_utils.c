/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:46:54 by jberay            #+#    #+#             */
/*   Updated: 2024/03/11 11:22:10 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_pipe(t_char_iter *iter, t_token *token)
{
	token->type = PIPE_TOKEN;
	token->location.start = char_iter_cursor(iter);
	token->location.len = 1;
	char_iter_next(iter);
}

void	take_redir_append(t_char_iter *iter, t_token *token)
{
	char	peek_next;

	peek_next = *(iter->start + 2);
	if (peek_next != *iter->end)
	{
		if (peek_next == '<'
			|| peek_next == '>'
			|| peek_next == *iter->end)
		{
			take_error(iter, token);
			return ;
		}
	}
	token->type = REDIR_APPEND_TOKEN;
	token->location.start = char_iter_cursor(iter);
	token->location.len = 2;
	char_iter_next(iter);
	char_iter_next(iter);
}

void	take_redir_heredoc(t_char_iter *iter, t_token *token)
{
	char	peek_next;

	peek_next = *(iter->start + 2);
	if (peek_next != *iter->end)
	{
		if (peek_next == '<'
			|| peek_next == '>'
			|| peek_next == *iter->end)
		{
			take_error(iter, token);
			return ;
		}
	}
	token->type = REDIR_HEREDOC_TOKEN;
	token->location.start = char_iter_cursor(iter);
	token->location.len = 2;
	char_iter_next(iter);
	char_iter_next(iter);
}

void	take_redir_in(t_char_iter *iter, t_token *token)
{
	char	peek_next;

	peek_next = *(iter->start + 1);
	if (peek_next != *iter->end)
	{
		if (peek_next == '<')
		{
			take_redir_heredoc(iter, token);
			return ;
		}
	}
	token->type = REDIR_IN_TOKEN;
	token->location.start = char_iter_cursor(iter);
	token->location.len = 1;
	char_iter_next(iter);
}

void	take_redir_out(t_char_iter *iter, t_token *token)
{
	char	peek_next;

	peek_next = *(iter->start + 1);
	if (peek_next != *iter->end)
	{
		if (peek_next == '>')
		{
			take_redir_append(iter, token);
			return ;
		}
	}
	token->type = REDIR_OUT_TOKEN;
	token->location.start = char_iter_cursor(iter);
	token->location.len = 1;
	char_iter_next(iter);
}

void	take_eol(t_char_iter *iter, t_token *token)
{
	token->type = EOL_TOKEN;
	token->location.start = char_iter_cursor(iter);
	token->location.len = 0;
}
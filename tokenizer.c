/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:33:19 by jberay            #+#    #+#             */
/*   Updated: 2024/03/11 15:27:11 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_error(t_char_iter *iter, t_token *token)
{
	token->type = ERROR_TOKEN;
	token->location.start = char_iter_cursor(iter);
	while (char_iter_cursor(iter) != iter->end)
	{
		char_iter_next(iter);
		token->location.len++;
	}
	token->location.len = 0;
}

int	ft_realloc(t_token **token, size_t size)
{
	t_token		*new;
	size_t		i;

	new = malloc(sizeof(t_token) * (size));
	if (!new)
	{
		printf("Error with malloc\n");
		return (1);
	}
	i = 0;
	while (i < size)
	{
		new[i] = (*token)[i];
		i++;
	}
	free(*token);
	*token = new;
	return (0);
}

/*
	checking for unclosed quotes ok
	check for redirection file name
	pipe with no command
*/

bool	is_redir_pipe_eol(t_token *token)
{
	if (token->type == REDIR_IN_TOKEN
		|| token->type == REDIR_OUT_TOKEN
		|| token->type == REDIR_APPEND_TOKEN
		|| token->type == REDIR_HEREDOC_TOKEN
		|| token->type == PIPE_TOKEN
		|| token->type == EOL_TOKEN)
		return (true);
	return (false);
}

int	check_syntax(t_token *token, int d_flag)
{
	size_t	i;

	i = 0;
	if (d_flag % 2 != 0)
	{
		printf("unclosed quotes\n");
		return (1);
	}
	if 
	while (token[i].type != EOL_TOKEN)
	{
		if (token[i].type == ERROR_TOKEN)
		{
			printf("error token\n");
			return (1);
		}
		if (is_redir_pipe_eol(&token[i]))
		{
			if (token[i + 1].type == SPACE_TOKEN)
				i++;
			if (is_redir_pipe_eol(&token[i + 1]))
			{
				printf("redirection file name\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

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
		take_dollar(iter, token);
	else if (iter->start[0] == '|' && *d_flag % 2 == 0)
		take_pipe(iter, token);
	else
		take_string(iter, token, d_flag);
}

int	tokenizer(char *read_line, t_token	**token_ptr_add)
{
	t_char_iter		iter;
	t_token			*token;
	int				d_flag;
	size_t			i;

	token = malloc (sizeof(t_token));
	if (!token)
		return (1);
	iter = char_iter_constructor(read_line, ft_strlen(read_line));
	i = 0;
	d_flag = 0;
	while (char_iter_cursor(&iter) != iter.end)
	{
		tokenizer_loop(&token[i], &iter, &d_flag);
		i++;
		if (ft_realloc(&token, i + 1))
			return (1);
	}
	take_eol(&iter, &token[i]);
	if (check_syntax(token, d_flag))
		return (1);
	*token_ptr_add = token;
	return (0);
}

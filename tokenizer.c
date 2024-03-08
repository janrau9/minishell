/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:33:19 by jberay            #+#    #+#             */
/*   Updated: 2024/03/08 14:16:40 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_error(t_char_iter *iter, t_token *token)
{
	token->type = ERROR_TOKEN;
	token->location.start = char_iter_cursor(iter);
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
	else if (iter->start[0] == '|')
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
	ft_lstnew_double(token);
	iter = char_iter_constructor(read_line, ft_strlen(read_line));
	i = 0;
	d_flag = 0;
	while (char_iter_cursor(&iter) != iter.end)
	{
		tokenizer_loop(&token[i++], &iter, &d_flag);
		if (token[i].type == ERROR_TOKEN)
		{
			printf("Error with token\n");
			exit(1);
		}
		if (ft_realloc(&token, i + 1))
			return (1);
	}
	take_eol(&iter, &token[i]);
	*token_ptr_add = token;
	return (0);
}

// int	tokenizer(char *read_line, t_token	**token_ptr_add)
// {
// 	t_char_iter		iter;
// 	t_token			*token;
// 	int				d_flag;
// 	size_t			i;

// 	token = malloc (sizeof(t_token));
// 	if (!token)
// 		return (1);
// 	iter = char_iter_constructor(read_line, ft_strlen(read_line));
// 	i = 0;
// 	d_flag = 0;
// 	while (char_iter_cursor(&iter) != iter.end)
// 	{
// 		if (char_iter_peek(&iter) == '<' && d_flag % 2 == 0)
// 			take_redir_in(&iter, &token[i++]);
// 		else if (char_iter_peek(&iter) == '>' && d_flag % 2 == 0)
// 			take_redir_out(&iter, &token[i++]);
// 		else if (char_iter_peek(&iter) == '\'' && d_flag % 2 == 0)
// 			take_squote(&iter, &token[i++]);
// 		else if (char_iter_peek(&iter) == ' ' && d_flag % 2 == 0)
// 			take_space(&iter, &token[i++]);
// 		else if (char_iter_peek(&iter) == '"')
// 			take_dquote(&iter, &token[i++], &d_flag);
// 		else if (char_iter_peek(&iter) == '$')
// 			take_dollar(&iter, &token[i++]);
// 		else if (char_iter_peek(&iter) == '|')
// 			take_pipe(&iter, &token[i++]);
// 		else
// 			take_string(&iter, &token[i++], &d_flag);
// 		if (token[i].type == ERROR_TOKEN)
// 			return (2);
// 		if (ft_realloc(&token, i + 1))
// 			return (1);
// 	}
// 	take_eol(&iter, &token[i]);
// 	*token_ptr_add = token;
// 	return (0);
// }

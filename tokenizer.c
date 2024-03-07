/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:33:19 by jberay            #+#    #+#             */
/*   Updated: 2024/03/07 15:02:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		take_error(t_char_iter *iter, t_token *token);

void	ft_realloc(t_token **token, int size)
{
	t_token	*new;
	int		i;

	new = malloc(sizeof(t_token) * (size));
	if (!new)
	{
		printf("Error with malloc\n");
		exit(1);
	}
	i = 0;
	while (i < size)
	{
		new[i] = (*token)[i];
		i++;
	}
	free(*token);
	*token = new;
}
int	tokenizer(char *read_line, t_token	**token_ptr_add)
{
	t_char_iter		iter;
	t_token			*token;
	int				d_flag;
	char			peek;
	size_t			i;

	token = *token_ptr_add;
	token = malloc (sizeof(t_token));
	if (!token)
	{
		printf("Error with malloc\n");
		exit(1);
	}
	iter = char_iter_constructor(read_line, strlen(read_line));
	i = 0;
	d_flag = 0;
	while (char_iter_cursor(&iter) != iter.end)
	{
		peek = char_iter_peek(&iter);
		if (char_iter_peek(&iter) == '<' && d_flag % 2 == 0)
			take_redir_in(&iter, &token[i]);
		else if (peek == '>' && d_flag % 2 == 0)
			take_redir_out(&iter, &token[i]);
		else if (peek == '"')
			take_dquote(&iter, &token[i], &d_flag);
		else if (peek == '\'' && d_flag % 2 == 0)
			take_squote(&iter, &token[i]);
		else if (peek == '$')
			take_dollar(&iter, &token[i]);
		else if (peek == ' ' && d_flag % 2 == 0)
			take_space(&iter, &token[i]);
		else
			take_string(&iter, &token[i], &d_flag);
		i++;
		ft_realloc(&token, i + 1);
	}
	take_eol(&iter, &token[i]);
	*token_ptr_add = token;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:48:54 by jberay            #+#    #+#             */
/*   Updated: 2024/03/08 12:53:45 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_string(char **dst, t_token **token_ptr_add, \
char *read_line, t_token_iter *iter_ptr)
{
	t_token			*token;
	t_token_iter	*iter;

	token = *token_ptr_add;
	iter = iter_ptr;
	ft_substr_custom(dst, read_line, \
	token->location.start, token->location.len);
	token_iter_next(iter_ptr);
	iter_ptr = iter;
}

void	parse_dollar(char **dst, t_token **token_ptr_add, \
char *read_line, t_token_iter *iter_ptr)
{
	char			*env_str;
	char			*expand_str;
	t_token			*token;
	t_token_iter	*iter;

	token = *token_ptr_add;
	iter = iter_ptr;
	ft_substr_custom(&env_str, read_line, \
	token->location.start, token->location.len);
	expand_str = getenv(env_str);
	if (!expand_str)
		expand_str = "";
	*dst = ft_strdup(expand_str);
	free(env_str);
	token_iter_next(iter);
	iter_ptr = iter;
}

/*
	** str[0] = string result
	** str[1] = parsed string
	** str[2] = temporary string to free
	** iter[0] = iter to iterate through tokens
	** iter[1] = iter pointer to pass to functions
*/

void	parse_dquote(char **dst, t_token **token, \
char *read_line, t_token_iter *iter_ptr)
{
	t_token_iter	*iter[2];
	char			*str[3];

	iter[0] = iter_ptr;
	iter[1] = iter_ptr;
	str[0] = ft_strdup("");
	while (token_iter_cursor(iter[0]) \
		<= token_iter_find(*token, CLOSE_DQUOTE_TOKEN))
	{
		str[2] = str[0];
		*token = token_iter_cursor(iter[0]);
		if (token_iter_cursor(iter[0])->location.len > 0)
		{
			if (token_iter_peek(iter[0]) == DOLLAR_TOKEN)
				parse_dollar(&str[1], token, read_line, iter[1]);
			else
				parse_string(&str[1], token, read_line, iter[1]);
			ft_strjoin_custom(&str[0], str[2], str[1]);
		}
		else
			token_iter_next(iter[0]);
		iter[0] = iter[1];
	}
	iter_ptr = iter[0];
	*dst = str[0];
}

void	parse(t_cmd *cmds, char *read_line)
{
	size_t			i;
	t_token			*token;
	t_token_iter	iter[2];

	token = cmds->token;
	cmds->cmd = ft_calloc(1, sizeof(char *));
	iter[0] = token_iter_value(token, EOL_TOKEN);
	iter[1] = iter[0];
	i = 0;
	while (token_iter_cursor(&iter[0]) != iter[0].end)
	{
		token = token_iter_cursor(&iter[0]);
		if (token_iter_peek(&iter[0]) != SPACE_TOKEN)
		{
			if (token_iter_peek(&iter[0]) == DOLLAR_TOKEN)
				parse_dollar(&cmds->cmd[i++], &token, read_line, &iter[1]);
			else if (token_iter_peek(&iter[0]) == OPEN_DQUOTE_TOKEN)
				parse_dquote(&cmds->cmd[i++], &token, read_line, &iter[1]);
			else
				parse_string(&cmds->cmd[i++], &token, read_line, &iter[1]);
			ft_realloc_array(&cmds->cmd, i + 1);
		}
		else
			token_iter_next(&iter[1]);
		iter[0] = iter[1];
	}
	cmds->cmd[i] = NULL;
}

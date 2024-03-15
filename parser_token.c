/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:00 by jberay            #+#    #+#             */
/*   Updated: 2024/03/15 14:52:29 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir(t_data *data, char **dst, t_iterator *iter)
{
	ft_substr_custom(dst, data->read_line, \
	data->token[iter->token_iter].location.start, \
	data->token[iter->token_iter].location.len);
	if (!dst)
		ft_error(data, "malloc error", MALLOC_ERROR);
	iter->token_iter = iter->token_iter + 1;
	iter->redir_iter = iter->redir_iter + 1;
}

/*Malloc substring from char* start and len in t_token struct*/
void	parse_string(t_data *data, char **dst, t_iterator *iter)
{
	ft_substr_custom(dst, data->read_line, \
	data->token[iter->token_iter].location.start, \
	data->token[iter->token_iter].location.len);
	if (!dst)
		ft_error(data, "malloc error", MALLOC_ERROR);
	iter->token_iter = iter->token_iter + 1;
}

/*Malloc substring and  expand $ variable*/
void	parse_dollar(t_data *data, char **dst, t_iterator *iter)
{
	char			*env_str;
	char			*expand_str;

	ft_substr_custom(&env_str, data->read_line, \
	data->token[iter->token_iter].location.start, \
	data->token[iter->token_iter].location.len);
	if (!env_str)
		ft_error(data, "malloc error", MALLOC_ERROR);
	expand_str = getenv(env_str);
	if (!expand_str)
		expand_str = "";
	*dst = ft_strdup(expand_str);
	if (!*dst)
		ft_error(data, "malloc error", MALLOC_ERROR);
	free(env_str);
	iter->token_iter = iter->token_iter + 1;
}

/*
	** Malloc substring until space or EOL_TOKEN
	** str[0] = string result
	** str[1] = parsed string
	** str[2] = temporary string to free
	** iter[0] = iter to iterate through tokens
	** iter[1] = iter pointer to pass to functions
*/
static bool	is_not_special_char(t_token *token)
{
	if (token->type != EOL_TOKEN
		&& token->type != SPACE_TOKEN
		&& token->type != REDIR_APPEND_TOKEN
		&& token->type != REDIR_IN_TOKEN
		&& token->type != REDIR_OUT_TOKEN
		&& token->type != REDIR_HEREDOC_TOKEN
		&& token->type != PIPE_TOKEN)
		return (true);
	return (false);
}

void	parse_dquote(t_data *data, char **dst, t_iterator *iter)
{
	size_t	quote;
	char	*str[3];

	quote = iter->token_iter;
	str[0] = ft_strdup("");
	if (!str[0])
		ft_error(data, "malloc error", MALLOC_ERROR);
	while (is_not_special_char(&data->token[quote]))
		quote++;
	while (iter->token_iter < quote)
	{
		str[2] = str[0];
		if (data->token[iter->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(data, &str[1], iter);
		else
			parse_string(data, &str[1], iter);
		ft_strjoin_custom(&str[0], str[2], str[1]);
		if (!str[0])
			ft_error(data, "malloc error", MALLOC_ERROR);
	}
	*dst = str[0];
}

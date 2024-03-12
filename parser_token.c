/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:13:00 by jberay            #+#    #+#             */
/*   Updated: 2024/03/12 14:13:01 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir(char **dst, t_data *data)
{
	ft_substr_custom(dst, data->read_line, \
	data->token[data->token_iter].location.start, \
	data->token[data->token_iter].location.len);
	data->token_iter = data->token_iter + 1;
	data->redir_iter = data->redir_iter + 1;
	ft_realloc_array(&data->cmd->redir, data->redir_iter + 1);
	if (data->token[data->token_iter].type == SPACE_TOKEN)
		data->token_iter = data->token_iter + 1;
	parse_dquote(&data->cmd->redir[data->redir_iter], data);
	data->redir_iter = data->redir_iter + 1;
	data->cmds_iter = data->cmds_iter - 1;
}

/*Malloc substring from char* start and len in t_token struct*/
void	parse_string(char **dst, t_data *data)
{
	ft_substr_custom(dst, data->read_line, \
	data->token[data->token_iter].location.start, \
	data->token[data->token_iter].location.len);
	data->token_iter = data->token_iter + 1;
}

/*Malloc substring and  expand $ variable*/
void	parse_dollar(char **dst, t_data *data)
{
	char			*env_str;
	char			*expand_str;

	ft_substr_custom(&env_str, data->read_line, \
	data->token[data->token_iter].location.start, \
	data->token[data->token_iter].location.len);
	expand_str = getenv(env_str);
	if (!expand_str)
		expand_str = "";
	*dst = ft_strdup(expand_str);
	free(env_str);
	data->token_iter = data->token_iter + 1;
}

/*
	** Malloc substring until space or EOL_TOKEN
	** str[0] = string result
	** str[1] = parsed string
	** str[2] = temporary string to free
	** iter[0] = iter to iterate through tokens
	** iter[1] = iter pointer to pass to functions
*/
void	parse_dquote(char **dst, t_data *data)
{
	size_t	quote;
	char	*str[3];

	quote = data->token_iter;
	str[0] = ft_strdup("");
	while (data->token[quote].type != EOL_TOKEN
		&& data->token[quote].type != SPACE_TOKEN
		&& data->token[quote].type != REDIR_APPEND_TOKEN
		&& data->token[quote].type != REDIR_IN_TOKEN
		&& data->token[quote].type != REDIR_OUT_TOKEN
		&& data->token[quote].type != REDIR_HEREDOC_TOKEN
		&& data->token[quote].type != PIPE_TOKEN)
		quote++;
	while (data->token_iter < quote)
	{
		str[2] = str[0];
		if (data->token[data->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(&str[1], data);
		else
			parse_string(&str[1], data);
		ft_strjoin_custom(&str[0], str[2], str[1]);
	}
	*dst = str[0];
}

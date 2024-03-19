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

void	parse_redir(t_exec *exec, char **dst, t_iterator *iter)
{
	ft_substr_custom(dst, exec->read_line, \
	exec->token[iter->token_iter].location.start, \
	exec->token[iter->token_iter].location.len);
	if (!dst)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	iter->token_iter = iter->token_iter + 1;
	iter->redir_iter = iter->redir_iter + 1;
}

/*Malloc substring from char* start and len in t_token struct*/
void	parse_string(t_exec *exec, char **dst, t_iterator *iter)
{
	ft_substr_custom(dst, exec->read_line, \
	exec->token[iter->token_iter].location.start, \
	exec->token[iter->token_iter].location.len);
	if (!dst)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	iter->token_iter = iter->token_iter + 1;
}

/*Malloc substring and  expand $ variable*/
void	parse_dollar(t_exec *exec, char **dst, t_iterator *iter, bool is_expand)
{
	char	*env_str;
	char	*expand_str;

	if (is_expand == 0)
	{
		exec->token[iter->token_iter].location.start--;
		exec->token[iter->token_iter].location.len++;
		parse_string(exec, dst, iter);
		return ;
	}
	ft_substr_custom(&env_str, exec->read_line, \
	exec->token[iter->token_iter].location.start, \
	exec->token[iter->token_iter].location.len);
	if (!env_str)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	expand_str = getenv(env_str);
	if (!expand_str)
		expand_str = "";
	*dst = ft_strdup(expand_str);
	if (!*dst)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	free(env_str);
	iter->token_iter = iter->token_iter + 1;
}


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
/*
	** Malloc substring until not special char
	** str[0] = string result
	** str[1] = parsed string
	** str[2] = temporary string to free
*/
void	parse_dquote(t_exec *exec, char **dst, t_iterator *iter, bool is_expand)
{
	size_t	quote;
	char	*str[3];

	quote = iter->token_iter;
	str[0] = ft_strdup("");
	if (!str[0])
		ft_error(exec, "malloc error", MALLOC_ERROR);
	while (is_not_special_char(&exec->token[quote]))
		quote++;
	while (iter->token_iter < quote)
	{
		str[2] = str[0];
		if (exec->token[iter->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(exec, &str[1], iter, is_expand);
		else
			parse_string(exec, &str[1], iter);
		ft_strjoin_custom(&str[0], str[2], str[1]);
		if (!str[0])
			ft_error(exec, "malloc error", MALLOC_ERROR);
	}
	*dst = str[0];
}

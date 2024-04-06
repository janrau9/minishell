/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:23:57 by jberay            #+#    #+#             */
/*   Updated: 2024/04/05 15:46:22 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_exp_token(t_exec *exec, char **dst, \
t_iterator *iter, bool is_expand)
{
	char	*str[3];

	str[0] = ft_strdup("");
	if (!str[0])
		ft_error(exec, "malloc error", MALLOC_ERROR);
	while (exec->token[iter->token_iter].type != EOL_TOKEN)
	{
		if (exec->token[iter->token_iter].type == REDIR_HEREDOC_TOKEN)
			is_expand = false;
		else if (exec->token[iter->token_iter].type == STRING_TOKEN
			|| exec->token[iter->token_iter].type == SQUOTE_TOKEN)
			is_expand = true;
		str[2] = str[0];
		if (exec->token[iter->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(exec, &str[1], iter, is_expand);
		else
		{
			set_start_len(exec, iter);
			parse_string(exec, &str[1], iter);
		}
		ft_strjoin_custom(&str[0], str[2], str[1]);
		if (!str[0])
			ft_error(exec, "malloc error", MALLOC_ERROR);
	}
	*dst = str[0];
}

int	expander(t_exec *exec)
{
	t_iterator	iter;
	char		*expanded;

	iter.token_iter = 0;
	iter.cmds_iter = 0;
	tokenizer(exec);
	if (check_syntax(exec->token))
		return (SYNTAX_ERROR);
	parse_exp_token(exec, &expanded, &iter, true);
	free(exec->token);
	exec->token = NULL;
	free(exec->read_line);
	exec->read_line = expanded;
	tokenizer(exec);
	if (check_syntax(exec->token))
		return (SYNTAX_ERROR);
	return (0);
}

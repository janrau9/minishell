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

void	parse_string(char **dst, t_token *token, \
char *read_line, size_t *iter)
{
	ft_substr_custom(dst, read_line, \
	token[*iter].location.start, token[*iter].location.len);
	*iter += 1;
}

void	parse_dollar(char **dst, t_token *token, \
char *read_line, size_t *iter)
{
	char			*env_str;
	char			*expand_str;

	ft_substr_custom(&env_str, read_line, \
	token[*iter].location.start, token[*iter].location.len);
	expand_str = getenv(env_str);
	if (!expand_str)
		expand_str = "";
	*dst = ft_strdup(expand_str);
	free(env_str);
	*iter += 1;
}

/*
	** str[0] = string result
	** str[1] = parsed string
	** str[2] = temporary string to free
	** iter[0] = iter to iterate through tokens
	** iter[1] = iter pointer to pass to functions
*/

void	parse_dquote(char **dst, t_token *token, \
char *read_line, size_t *iter)
{
	size_t			i;
	char			*str[3];

	str[0] = ft_strdup("");
	i = *iter;
	size_t j = i;
	while (token[j].type != EOL_TOKEN && token[j].type != SPACE_TOKEN)
	{
		j++;
	}
	while (i < j)
	{
		str[2] = str[0];
		if (token[i].type == DOLLAR_TOKEN)
			parse_dollar(&str[1], token, read_line, &i);
		else
			parse_string(&str[1], token, read_line, &i);
		ft_strjoin_custom(&str[0], str[2], str[1]);
	}
	*iter = i;
	*dst = str[0];
}

void	parse(t_cmd *cmds, char *read_line)
{
	size_t			i;
	size_t			t_iter;
	t_token			*token;
	t_list			*head;

	token = cmds->token;
	cmds->cmd = ft_calloc(1, sizeof(char *));
	i = 0;
	t_iter = 0;
	while (token[t_iter].type != EOL_TOKEN)
	{
		if (token[t_iter].type != SPACE_TOKEN)
		{
			if (token[t_iter].type == DOLLAR_TOKEN)
				parse_dollar(&cmds->cmd[i++], token, read_line, &t_iter);
			else if (token[t_iter].type == OPEN_DQUOTE_TOKEN)
				parse_dquote(&cmds->cmd[i++], token, read_line, &t_iter);
			else
				parse_string(&cmds->cmd[i++], token, read_line, &t_iter);
			ft_realloc_array(&cmds->cmd, i + 1);
		}
		else
			t_iter = t_iter + 1;
	}
	cmds->cmd[i] = NULL;
}

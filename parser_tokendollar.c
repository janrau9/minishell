/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokendollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:51:16 by jberay            #+#    #+#             */
/*   Updated: 2024/03/26 11:54:54 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getenv_loop(t_exec *exec, char *key, size_t i)
{
	char	*value;

	if (ft_strncmp(exec->envp[i], key, ft_strlen(key)) == 0)
	{
		value = ft_strdup(exec->envp[i] + ft_strlen(key));
		if (!value)
		{
			free(key);
			ft_error(exec, "malloc error", MALLOC_ERROR);
		}
		free(key);
		return (value);
	}
	return (NULL);
}

char	*ft_getenv(t_exec *exec, char *key)
{
	size_t	i;
	char	*tmp;

	tmp = key;
	key = ft_strjoin(tmp, "=");
	if (!tmp)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	free(tmp);
	i = -1;
	while (exec->envp[++i])
		return (ft_getenv_loop(exec, key, i));
	free(key);
	return (NULL);
}

static void	not_exp(t_exec *exec, char **dst, t_iterator *iter)
{
	exec->token[iter->token_iter].location.start--;
	exec->token[iter->token_iter].location.len++;
	parse_string(exec, dst, iter);
}

/*Malloc substring and  expand $ variable*/
void	parse_dollar(t_exec *exec, char **dst, t_iterator *iter, bool is_expand)
{
	char	*env_str;
	char	*expand_str;

	if (is_expand == 0)
		return (not_exp(exec, dst, iter));
	ft_substr_custom(&env_str, exec->read_line, \
	exec->token[iter->token_iter].location.start, \
	exec->token[iter->token_iter].location.len);
	if (!env_str)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	if (ft_strncmp(env_str, "?", 2) == 0)
		expand_str = ft_itoa(exec->exit_code);
	else if (iter->cmds_iter > 0
		&& !ft_strncmp(exec->cmd[iter->cmd_count].cmd[iter->cmds_iter - 1], \
		"unset", 6))
		expand_str = env_str;
	else
	{
		expand_str = ft_getenv(exec, env_str);
		if (!expand_str)
			expand_str = ft_strdup("");
	}
	*dst = expand_str;
	iter->token_iter = iter->token_iter + 1;
}

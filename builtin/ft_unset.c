/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:14:56 by jtu               #+#    #+#             */
/*   Updated: 2024/03/26 12:26:20 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_arr(char **envp, char *var)
{
	int		i;
	char	*var_equal;

	i = 0;
	var_equal = ft_strjoin(var, "=");
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var_equal, ft_strlen(var_equal) + 1))
		{
			free(var_equal);
			return (i);
		}
		if (ft_strnstr(envp[i], var, ft_strlen(var) + 1)
			&& ft_strlen(envp[i]) == ft_strlen(var))
		{
			free(var_equal);
			return (i);
		}
		i++;
	}
	free(var_equal);
	return (-1);
}

// int	ft_arrlen(char **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 		i++;
// 	return (i);
// }

int	ft_unset(t_exec *exec, char **cmd)
{
	int	i;
	int	j;
	int	rm;
	int	len;

	(void)cmd;
	i = 1;
	j = -1;
	rm = 0;
	len = 0;
	len = ft_arrlen(exec->envp);
	if (!cmd[i])
		return (0);
	while (cmd[i])
	{
		j = is_in_arr(exec->envp, cmd[i]);
		if (j >= 0)
		{
			free(exec->envp[j]);
			while (j < len)
			{
				exec->envp[j] = exec->envp[j + 1];
				j++;
			}
			exec->envp[len - 1 - rm] = NULL;
			rm++;
		}
		i++;
	}
	return (0);
}

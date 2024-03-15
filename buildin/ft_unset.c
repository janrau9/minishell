/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:14:56 by jtu               #+#    #+#             */
/*   Updated: 2024/03/15 16:22:47 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_arr(char **envp, char *var)
{
	int		i;
	char	*var_equal;

	i = 0;
	var_equal = ft_strjoin(var, '=');
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var, ft_strlen(var) + 1))
		{
			free(var_equal);
			return (i);
		}
		if (ft_strnstr(envp[i], var_equal, ft_strlen(var_equal)))
		{
			free(var_equal);
			return (i);
		}
		i++;
	}
	free(var_equal);
	return (-1);
}

// void	remove_var(t_exec *exec)
// {
// 	int	i;

// 	i = 0;
// 	while ()

// }

void	ft_unset(t_exec *exec, t_cmd *cmd)
{
	int	i;
	int	j;
	int	rm;
	int	len;

	i = 1;
	j = -1;
	rm = 0;
	len = ;
	if (!exec->cmd->cmd[i])
		return ;
	while (exec->cmd->cmd[i])
	{
		j = is_in_arr(exec->envp, exec->cmd->cmd[i]);
		if (j >= 0)
		{
			free(exec->envp[j]);
			while ()
				exec->envp[j] = exec->envp[j + 1];
			rm++;
		}
	}
	while (rm)
		exec->envp[ - 1 - rm] = NULL;
}

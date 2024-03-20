/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:09:55 by jberay            #+#    #+#             */
/*   Updated: 2024/03/15 09:10:49 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Malloced
** 1. exec->read_line
** 2. exec->token
** 3. exec->exec.cmd
** 4. exec->exec.envp
*/
void	ft_freearr(char ***array)
{
	size_t	i;
	char	**tmp;

	i = 0;
	if (!*array || !array)
		return ;
	tmp = *array;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	*array = NULL;
}

void	ft_freestruct(t_cmd **cmd)
{
	t_cmd	*tmp;
	size_t	i;

	tmp = *cmd;
	i = 0;
	while (tmp[i].cmd[0] != NULL)
	{
		ft_freearr(&tmp[i].cmd);
		ft_freearr(&tmp[i].redir);
		i++;
	}
	free(tmp);
	*cmd = NULL;
}

void ft_freeall(t_exec *exec)
{
	if (exec->read_line)
		free(exec->read_line);
	if (exec->token)
		free(exec->token);
	if (exec->pid)
		free(exec->pid);
	if (exec->cmd)
		ft_freestruct(&exec->cmd);
	if (exec->envp)
		ft_freearr(&exec->envp);
}

void ft_freeall_n_envp(t_exec *exec)
{
	if (exec->read_line)
		free(exec->read_line);
	if (exec->token)
		free(exec->token);
	if (exec->pid)
		free(exec->pid);
	if (exec->cmd)
		ft_freestruct(&exec->cmd);
}
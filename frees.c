/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:09:55 by jberay            #+#    #+#             */
/*   Updated: 2024/03/25 10:25:49 by jberay           ###   ########.fr       */
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

	tmp = *array;
	i = 0;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	*array = NULL;
}
void	ft_freepipes(t_exec *exec)
{
	size_t	i;
	int	**tmp;

	tmp = exec->pipes;
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	exec->pipes = NULL;
}

void	ft_freestruct(t_cmd **cmd)
{
	t_cmd	*tmp;
	size_t	i;

	tmp = *cmd;
	i = 0;
	while (tmp[i].cmd != NULL
		|| tmp[i].redir != NULL)
	{
		if (tmp[i].cmd)
			ft_freearr(&tmp[i].cmd);
	 	if (tmp[i].redir)
			ft_freearr(&tmp[i].redir);
		i++;
	}
	free(tmp);
	*cmd = NULL;
}

void	ft_freeall(t_exec *exec)
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
	if (exec->pipes)
		ft_freepipes(exec);
}

void	ft_freeall_n_envp(t_exec *exec)
{
	if (exec->read_line)
		free(exec->read_line);
	if (exec->token)
		free(exec->token);
	if (exec->pid)
		free(exec->pid);
	if (exec->cmd)
	 	ft_freestruct(&exec->cmd);
	if (exec->pipes)
		ft_freepipes(exec);
}
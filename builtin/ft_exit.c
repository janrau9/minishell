/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:00:40 by jberay            #+#    #+#             */
/*   Updated: 2024/03/22 10:10:42 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_exit(t_exec *exec, char **cmd)
{
	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_putstr_fd("jjsh-1.0$ exit: too many arguments\n", 2);
			ft_freeall(exec);
			exec->exit_code = 1;
			exit (1);
		}
		ft_freeall(exec);
		exec->exit_code = ft_atoi(cmd[1]);
		exit (ft_atoi(cmd[1]));
	}
	ft_freeall(exec);
	exec->exit_code = 0;
	exit (0);
	return (0);
}
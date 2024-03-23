/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:00:40 by jberay            #+#    #+#             */
/*   Updated: 2024/03/22 12:29:26 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_exit(t_exec *exec, char **cmd)
{
	int	tmp;
	//int	i;

	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_putstr_fd("jjsh-1.0$ exit: too many arguments\n", 2);
			ft_freeall(exec);
			exec->exit_code = 1;
			exit (1);
		}
		tmp = ft_atoi(cmd[1]);
		//printf("tmp: %d\n", tmp);
		if (tmp == 0 && cmd[1][0] != '0')
		{
			ft_putstr_fd("jjsh-1.0$ exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_freeall(exec);
			exec->exit_code = 2;
			exit (2);
		}
		exec->exit_code = tmp;
		if (tmp < 0)
			exec->exit_code = 256 + tmp;
		ft_freeall(exec);
		exit (exec->exit_code);
	}
	ft_freeall(exec);
	exec->exit_code = 0;
	exit (0);
	return (0);
}

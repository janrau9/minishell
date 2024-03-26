/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:00:40 by jberay            #+#    #+#             */
/*   Updated: 2024/03/26 11:38:54 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
exit at LONG MAX = -1
exit at LONG MIN = 0
*/

static void	is_overflow(t_exec *exec, char *cmd, int ato)
{
	if (ato == 0 && ft_strncmp(cmd, "0", 2) == 0)
		return ;
	else if (ato == 0 && ft_strncmp(cmd, "-9223372036854775808", 21) == 0)
		return ;
	else if (ato == -1 && ft_strncmp(cmd, "-1", 3) == 0)
		return ;
	else if (ato == -1 && ft_strncmp(cmd, "9223372036854775807", 20) == 0)
		return ;
	ft_putstr_fd("jjsh-1.0$ exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_freeall(exec);
	exec->exit_code = 255;
	exit (255);
}

int	ft_exit(t_exec *exec, char **cmd)
{
	int	tmp;

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
		if (tmp == 0 || tmp == -1)
			is_overflow(exec, cmd[1], tmp);
		exec->exit_code = tmp;
		if (tmp < 0)
			exec->exit_code = 256 + tmp;
		ft_freeall(exec);
		exit (exec->exit_code);
	}
	ft_freeall(exec);
	exec->exit_code = 0;
	if (isatty(0))
		write(2, "exit\n", 5);
	exit (0);
}

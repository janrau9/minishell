/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:46:33 by jtu               #+#    #+#             */
/*   Updated: 2024/03/13 14:39:03 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (cmd[i] == "-n")
	{
		nl = 0;
		i++;
	}
	while (cmd[i])
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
	if (nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
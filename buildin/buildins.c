/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:18:54 by jtu               #+#    #+#             */
/*   Updated: 2024/03/14 14:30:05 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (ft_strncmp(cmd[i], "-n", 3))
	{
		nl = 0;
		i++;
	}
	while (cmd[i])
		ft_putstr_fd(cmd[i++], STDOUT_FILENO);
	if (nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strrchr(envp[i], '='))
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
}

void	ft_pwd()
{
	char	buffer[1024];

	getcwd(buffer, 1024);
	ft_putendl_fd(buffer, STDOUT_FILENO);
}

void	check_buildins(char **cmd, char **envp)
{
	if (!ft_strncmp(cmd[0], "env", 4))
		ft_env(envp);
	if (!ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd();
	if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
}
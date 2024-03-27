/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:18:54 by jtu               #+#    #+#             */
/*   Updated: 2024/03/27 15:23:46 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_exec *exec, char **cmd)
{
	int	i;
	int	nl;

	(void)exec;
	i = 1;
	nl = 0;
	if (!cmd[i])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (!ft_strncmp(cmd[i], "-n", 3))
		nl = i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	ft_env(t_exec *exec, char **cmd)
{
	int	i;

	(void)cmd;
	i = 0;
	while (exec->envp[i])
	{
		if (ft_strrchr(exec->envp[i], '='))
			ft_putendl_fd(exec->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	ft_pwd(t_exec *exec, char **cmd)
{
	char	buffer[1024];
	char	*buf;

	(void)cmd;
	(void)exec;
	char *stat = getcwd(buffer, 1024);
	if (!stat)
	{
		char *p = ft_strdup("PWD");
		buf = ft_getenv(exec, p);
		ft_putendl_fd(buf, STDOUT_FILENO);
		free(buf);
		return (0);
	}
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (0);
}

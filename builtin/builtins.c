/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:18:54 by jtu               #+#    #+#             */
/*   Updated: 2024/03/22 10:17:03 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_exec *exec, char **cmd)
{
	int	i;
	int	nl;

	(void)exec;
	i = 1;
	nl = 1;
	if (!ft_strncmp(cmd[i], "-n", 3))
	{
		nl = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl)
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

	(void)cmd;
	(void)exec;
	getcwd(buffer, 1024);
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (0);
}

int	check_builtins(t_exec *exec, char **cmd)
{
	if (!ft_strncmp(cmd[0], "env", 4))
	{
		ft_env(exec, cmd);
		exit (0);
	}
	else if (!ft_strncmp(cmd[0], "pwd", 4))
	{
		ft_pwd(exec, cmd);
		exit (0);
	}
	else if (!ft_strncmp(cmd[0], "echo", 5))
	{
		ft_echo(exec, cmd);
		exit (0);
	}
	else if (!ft_strncmp(cmd[0], "cd", 3))
	{
		ft_cd(exec, cmd);
		exit(0);
	}
	else if (!ft_strncmp(cmd[0], "export", 7))
	{
		ft_export(exec, cmd);
		exit (0);
	}
	else if (!ft_strncmp(cmd[0], "exit", 5))
	{
		ft_exit(exec, cmd);
	}
	return (0);
	// else if (!ft_strncmp(cmd[0], "unset", 6))
	// 	ft_unset(cmd, envp);
}
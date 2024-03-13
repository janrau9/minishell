/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:23:45 by jberay            #+#    #+#             */
/*   Updated: 2024/03/13 15:43:16 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_data *data)
{
	t_exec	*exec;

	exec = &data->exec;
	if (ft_strncmp(exec->cmd->cmd[0], "export", 7) == 0)
		ft_export(exec);
	// else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
	// 	ft_echo(cmd);
	// else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
	// 	ft_cd(cmd);
	// else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
	// 	ft_pwd(cmd);
	// else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
	// 	ft_unset(cmd);
	// else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
	// 	ft_env(cmd);
	// else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
	// 	ft_exit(cmd);
	return ;
}

int	rd_export_arg(t_exec *exec, char *exp_arg)
{
	size_t	c;
	size_t	len;
	char	*env;
	char	*tmp;

	c = -1;
	while (exp_arg[++c])
	{
		if (ft_isalnum(exp_arg[c]) == 0 && exp_arg[c] != '_' && exp_arg[c] != '=')
		{
			ft_putstr_fd("jjsh-1.0$ export: `", 2);
			ft_putstr_fd(exp_arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		if (exp_arg[c] == '=')
			len = c;
	}
	c = -1;
	tmp = ft_substr(exp_arg, 0, len + 1);
	if (!tmp)
		return (2);
	while (exec->envp[++c])
	{
		if (ft_strnstr(exec->envp[c], tmp, len + 1) != NULL)
		{
			env = exec->envp[c];
			free(env);
			free(tmp);
			exec->envp[c] = ft_strdup(exp_arg);
			return (1);
		}
	}
	free(tmp);
	return (0);
}

void	ft_export(t_exec *exec)
{
	size_t	size;
	char	**env;

	if (rd_export_arg(exec, exec->cmd[0].cmd[1]))
		return ;
	size = ft_arrlen(exec->envp);
	env = ft_calloc(size + 1, sizeof(char *));
	if (!env)
		exit(2);
	ft_arrcpy(&env, exec->envp);
	free(exec->envp);
	env[size] = ft_strdup(exec->cmd[0].cmd[1]);
	env[size + 1] = NULL;
	exec->envp = env;
}

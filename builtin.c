/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:23:45 by jberay            #+#    #+#             */
/*   Updated: 2024/03/21 09:05:08 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_export(t_exec *exec, char *exp_arg, size_t len)
{
	char	*tmp;
	char	*env;
	size_t	c;

	tmp = ft_substr(exp_arg, 0, len);
	if (!tmp)
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	c = -1;
	while (exec->envp[++c])
	{
		if (ft_strnstr(exec->envp[c], tmp, len) != NULL)
		{
			env = exec->envp[c];
			free(env);
			free(tmp);
			exec->envp[c] = ft_strdup(exp_arg);
			if (!exec->envp[c])
				ft_error(exec, "Malloc error\n", MALLOC_ERROR);
			return (1);
		}
	}
	free(tmp);
	return (0);
}

int	rd_export_arg(t_exec *exec, char *exp_arg)
{
	size_t	c;
	size_t	len;

	c = -1;
	len = 0;
	while (exp_arg[++c])
	{
		if (ft_isalnum(exp_arg[c]) == 0 && \
		exp_arg[c] != '_' && exp_arg[c] != '=')
		{
			ft_putstr_fd("jjsh-1.0$ export: `", 2);
			ft_putstr_fd(exp_arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit (1);
		}
		if (exp_arg[c] == '=')
			len = c + 1;
	}
	return (run_export(exec, exp_arg, len));
}

int	ft_export(t_exec *exec)
{
	size_t	size;
	char	**env;

	if (rd_export_arg(exec, exec->cmd[0].cmd[1]))
		return (1);
	size = ft_arrlen(exec->envp);
	env = ft_calloc(size + 1, sizeof(char *));
	if (!env)
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	ft_arrcpy(&env, exec->envp);
	free(exec->envp);
	env[size] = ft_strdup(exec->cmd[0].cmd[1]);
	if (!env[size])
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	env[size + 1] = NULL;
	exec->envp = env;
	return (0);
}


// void	ft_pwd(void)
// {
// 	char	buffer[1024];

// 	getcwd(buffer, 1024);
// 	ft_putendl_fd(buffer, STDOUT_FILENO);
// }

void	builtin(t_exec *exec)
{
	if (exec->cmd[0].cmd[0] == NULL)
		return ;
	if (!ft_strncmp(exec->cmd[0].cmd[0], "export", 7))
		ft_export(exec);
	// else if (!ft_strncmp(exec->cmd->cmd[0], "echo", 5))
	// 	ft_echo(&exec->cmd[0].cmd[1]);
	// else if (!ft_strncmp(exec->cmd->cmd[0], "cd", 3))
	// 	ft_cd(&exec->cmd[0].cmd);
	// else if (!ft_strncmp(exec->cmd->cmd[0], "pwd", 4))
	// 	ft_pwd();
	// else if (!ft_strncmp(exec->cmd->cmd[0], "unset", 6))
	// 	ft_unset(&exec->cmd);
	// else if (!ft_strncmp(exec->cmd->cmd[0], "env", 4))
	// 	ft_env(exec->envp);
	// else if (!ft_strncmp(exec->cmd->cmd[0], "exit", 5))
	// 	ft_exit(&exec->cmd);
	return ;
}
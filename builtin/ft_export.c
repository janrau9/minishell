/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:23:45 by jberay            #+#    #+#             */
/*   Updated: 2024/04/04 08:21:38 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (2);
		}
	}
	free(tmp);
	return (0);
}

int	rd_export_arg(t_exec *exec, char *exp_arg)
{
	size_t	c;

	c = 0;
	while (1)
	{
		if ((ft_isalnum(exp_arg[c]) == 0 && exp_arg[c] != '_'
				&& exp_arg[c] != '=') || ft_isdigit(exp_arg[0])
			|| exp_arg[0] == '=' || exp_arg[0] == '\0')
		{
			ft_putstr_fd("jjsh: export: `", 2);
			ft_putstr_fd(exp_arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		if (exp_arg[c] == '=')
		{
			c++;
			break ;
		}
		c++;
		if (exp_arg[c] == '\0')
			break ;
	}
	return (run_export(exec, exp_arg, c));
}

int	print_export(t_exec *exec)
{
	size_t	i;

	i = -1;
	while (exec->envp[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(exec->envp[i], STDOUT_FILENO);
	}
	return (0);
}

void	call_export(t_exec *exec, char *cmd)
{
	size_t	size;
	char	**env;

	size = ft_arrlen(exec->envp);
	env = ft_calloc(size + 2, sizeof(char *));
	if (!env)
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	ft_arrcpy(&env, exec->envp);
	free(exec->envp);
	env[size] = ft_strdup(cmd);
	if (!env[size])
		ft_error(exec, "Malloc error\n", MALLOC_ERROR);
	env[size + 1] = NULL;
	exec->envp = env;
}

int	ft_export(t_exec *exec, char **cmd)
{
	size_t	i;
	int		ret;

	if (!cmd[1])
		return (print_export(exec));
	i = 0;
	while (cmd[++i])
	{
		ret = rd_export_arg(exec, cmd[i]);
		if (ret == 1)
			return (1);
		if (ret == 2)
			continue ;
		call_export(exec, cmd[i]);
	}
	return (0);
}

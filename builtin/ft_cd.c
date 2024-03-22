/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:56:50 by jtu               #+#    #+#             */
/*   Updated: 2024/03/22 10:08:43 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_home(char **envp)
{
	char	*home_path;

	while (*envp && !ft_strnstr(*envp, "HOME=", 5))
		envp++;
	if (!*envp)
		error_exit(NO_PATH, NULL);
	home_path = *envp + 5;
	return (home_path);
}

int	ft_cd(t_exec *exec, char **cmd)
{
	if (!ft_strncmp(cmd[1], "~", 2))
		cmd[1] = find_home(exec->envp);
	chdir(cmd[1]);
	return (0);
}

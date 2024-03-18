/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:56:50 by jtu               #+#    #+#             */
/*   Updated: 2024/03/14 16:30:34 by jtu              ###   ########.fr       */
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

void	ft_cd(char **cmd, char **envp)
{
	if (!ft_strncmp(cmd[1], "~", 2))
		cmd[1] = find_home(envp);
	chdir(cmd[1]);
}

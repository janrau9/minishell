/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:56:50 by jtu               #+#    #+#             */
/*   Updated: 2024/03/26 11:48:03 by jberay           ###   ########.fr       */
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
	struct stat	buf;
	char		buffer[1024];
	char		*old[3];

	getcwd(buffer, 1024);
	old[0] = "export";
	old[1] = ft_strjoin("OLDPWD=", buffer);
	if (!old[1])
		ft_error(exec, "malloc error", MALLOC_ERROR);
	old[2] = NULL;
	if (ft_arrlen(cmd) > 2)
		return (0);
	if (!ft_strncmp(cmd[1], "~", 2))
		cmd[1] = find_home(exec->envp);
	if (stat(cmd[1], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			chdir(cmd[1]);
		else
			error_exit(NO_PATH, cmd[1]);
	}
	else
		error_exit(STAT_FAIL, cmd[1]);
	ft_export(exec, old);
	return (0);
}

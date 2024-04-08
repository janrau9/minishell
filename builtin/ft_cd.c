/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:56:50 by jtu               #+#    #+#             */
/*   Updated: 2024/04/08 10:44:42 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_home(t_exec *exec, char **envp)
{
	char	*home_path;

	while (*envp && !ft_strnstr(*envp, "HOME=", 5))
		envp++;
	if (!*envp)
		error_exit(exec, error_msg(NULL, strerror(errno), true), 1, false);
	home_path = *envp + 5;
	return (home_path);
}

void	update_pwd(t_exec *exec, char *buffer)
{
	char	*old[3];
	char	*key;
	char	*pwd;
	static int	i = 0;

	old[0] = "export";
	old[2] = NULL;
	key = ft_strdup("OLDPWD");
	if (i==0)
	{
		pwd = buffer;
		i++;
	}
	else
		pwd = ft_getenv(exec, key);
	if (pwd != NULL)
	{
		old[1] = ft_strjoin("OLDPWD=", buffer);
		if (!old[1])
			ft_error(exec, "malloc error", MALLOC_ERROR);
		ft_export(exec, old);
		free(old[1]);
	}
	key = ft_strdup("PWD");
	pwd = ft_getenv(exec, key);
	if (pwd != NULL)
	{
		getcwd(buffer, 1024);
		old[1] = ft_strjoin("PWD=", buffer);
		if (!old[1])
			ft_error(exec, "malloc error", MALLOC_ERROR);
		old[2] = NULL;
		ft_export(exec, old);
		free(old[1]);
	}
	free(pwd);
}

int	cd_stat(t_exec *exec, char *dir)
{
	struct stat	buf;

	if (!stat(dir, &buf))
	{
		if (S_ISDIR(buf.st_mode) && chdir(dir) == -1)
			return (error_exit(exec, error_msg(dir, \
				"Permission denied", true), 126, false));
		else if (!S_ISDIR(buf.st_mode))
			return (error_exit(exec, error_msg(dir, \
				"Not a directory", true), 127, false));
		else
			return (0);
	}
	else
		return (error_exit(exec, error_msg(dir, \
			"No such file or directory", true), 126, false));
}

int	ft_cd(t_exec *exec, char **cmd)
{
	char		buffer[1024];
	char		*home;
	char		*err_msg;
	char		*dir;

	getcwd(buffer, 1024);
	dir = cmd[1];
	if (ft_arrlen(cmd) < 2 || !ft_strncmp(cmd[1], "~", 2))
	{
		home = ft_strdup("HOME");
		dir = ft_getenv(exec, home);
		if (!dir)
		{
			err_msg = ft_strdup("cd: HOME not set\n");
			return (error_exit(exec, err_msg, 1, false));
		}
	}
	if (cd_stat(exec, dir))
		return (1);
	if (ft_arrlen(cmd) < 2 || !ft_strncmp(cmd[1], "~", 2))
		free(dir);
	//update_oldpwd(exec, buffer);
	update_pwd(exec, buffer);
	return (0);
}

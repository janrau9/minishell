/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:50:50 by jtu               #+#    #+#             */
/*   Updated: 2024/03/27 14:49:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	int		i;
	int		j;
	char	*joined_str;

	i = 0;
	j = 0;
	joined_str = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!joined_str)
		return (NULL);
	while (s1[i])
		joined_str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joined_str[j++] = s2[i++];
	i = 0;
	while (s3[i])
		joined_str[j++] = s3[i++];
	joined_str[j] = '\0';
	return (joined_str);
}

/*get error type, give an error message and exit the project*/
int	error_exit(t_exec *exec, t_error error, char *s)
{
	char	*err_msg;
	char	*temp;

	if (error == CMD_NOT_FOUND)
	{
		err_msg = ft_strjoin_3("jjsh: ", s, ": command not found\n");
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
		free(err_msg);
		ft_freeall_n_envp(exec);
		if (exec->parent)
			return (1);
		exit(127);
	}
	if (error == NO_PATH)
	{
		err_msg = ft_strjoin_3("jjsh: ", s, ": No such file or directory\n");
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
		free(err_msg);
		ft_freeall_n_envp(exec);
		if (exec->parent)
			return (1);
		exit(127);
	}
	if (error == IS_DIR)
	{
		err_msg = ft_strjoin_3("jjsh: ", s, ": is a directory\n");
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
		free(err_msg);
		ft_freeall_n_envp(exec);
		if (exec->parent)
			return (1);
		exit(126);
	}
	if (error == EXECVE_FAIL || error == STAT_FAIL)
	{
		if (!s)
			s = "\n";
		err_msg = ft_strjoin_3("jjsh: ", s, ": Permission denied\n");
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
		free(err_msg);
		// if (!exec->cmd)
		// 	ft_putstr_fd("NULL EXEC", 2);
		ft_freeall_n_envp(exec);
		if (exec->parent)
			return (1);
		exit(126);
	}
	ft_putstr_fd("cd error", STDERR_FILENO);
	temp = ft_strjoin_3(": ", strerror(errno), "\n");
	err_msg = ft_strjoin_3("jjsh: ", s, temp);
	free(temp);
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
	free(err_msg);
	ft_freeall_n_envp(exec);
	if (exec->parent)
		return (1);
	exit(EXIT_FAILURE);
}

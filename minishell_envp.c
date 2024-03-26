/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:54:13 by jberay            #+#    #+#             */
/*   Updated: 2024/03/26 11:36:18 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_exec *exec)
{
	char	*tmp;
	char	*shlvl;
	int		lvl;
	char	*cmd[3];

	shlvl = getenv("SHLVL");
	lvl = ft_atoi(shlvl);
	tmp = ft_itoa(++lvl);
	if (!tmp)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	cmd[0] = "export";
	cmd[1] = ft_strjoin("SHLVL=", tmp);
	if (!cmd[1])
		ft_error(exec, "malloc error", MALLOC_ERROR);
	cmd[2] = NULL;
	ft_export(exec, cmd);
	free(tmp);
	free(cmd[1]);
}

void	make_envp(t_exec *exec, char **envp)
{
	int		envp_status;
	char	*old[3];

	old[0] = "unset";
	old[1] = "OLDPWD";
	old[2] = NULL;
	envp_status = ft_arrdup(&exec->envp, envp);
	if (envp_status == MALLOC_ERROR)
		exit (MALLOC_ERROR);
	else if (envp_status == NULL_ERROR)
		exec->envp = NULL;
	exec->exit_code = 0;
	update_shlvl(exec);
	if (isatty(0))
		ft_unset(exec, old);
}

void	make_history(t_exec *exec)
{
	char	*history;
	char	*tmp;

	exec->history_fd = open(".history.txt", O_CREAT | O_RDWR, 0644);
	if (exec->history_fd == -1)
		ft_error(exec, "history file error", MALLOC_ERROR);
	history = get_next_line(exec->history_fd);
	while (history)
	{
		tmp = ft_strtrim(history, "\n");
		if (!tmp)
			ft_error(exec, "malloc error", MALLOC_ERROR);
		add_history(tmp);
		free(history);
		free(tmp);
		history = get_next_line(exec->history_fd);
	}
}

int	ft_addhistory(t_exec *exec)
{
	char	*tmp;

	tmp = exec->read_line;
	write(exec->history_fd, exec->read_line, \
	ft_strlen(exec->read_line));
	write(exec->history_fd, "\n", 1);
	add_history(exec->read_line);
	exec->read_line = ft_strtrim(tmp, " ");
	if (!exec->read_line)
		ft_error(exec, "malloc error", MALLOC_ERROR);
	free(tmp);
	if (!*exec->read_line)
		return (1);
	return (0);
}

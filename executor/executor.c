/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:40 by jtu               #+#    #+#             */
/*   Updated: 2024/03/07 19:28:06 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*get the command from parser and create pipes and child process*/
void	executor(t_list *parsed_cmd, t_util *util)
{
	t_cmd	*cmd;
	int		fd[2];
	int		*pid;
	int		i;
	int		j;
	int		fd_in;
	int		status;

	i = 0;
	cmd = (t_cmd *)parsed_cmd->content;
	while (parsed_cmd)
	{
		if (parsed_cmd->next)
			pipe(fd);
		pid[i] = fork();
		if (pid[i] < 0)
			error(); //
		if (util->here_doc)
		{
			close(fd[0]);
			fd_in = open();
		}
		else
			fd_in = fd[0];
		parsed_cmd = parsed_cmd->next;
		i++;
	}
	j = 0;
	while (j++ < i)
		waitpid(pid[i], NULL, 0);
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		util->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		util->exit_code = WTERMSIG(status);
}

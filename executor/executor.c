/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:40 by jtu               #+#    #+#             */
/*   Updated: 2024/03/07 17:56:22 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	executor(t_list *parsed_cmd)
{
	t_cmd	*cmd;
	int		fd[2];
	int		*pid;
	int		i;

	i = 0;
	cmd = (t_cmd *)parsed_cmd->content;
	while (parsed_cmd)
	{
		if (parsed_cmd->next)
			pipe(fd);
		pid[i] = fork();
		parsed_cmd = parsed_cmd->next;
	}
}
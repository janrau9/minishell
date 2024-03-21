/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:48:54 by jberay            #+#    #+#             */
/*   Updated: 2024/03/15 14:51:12 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_redir_and_filename(t_exec *exec, t_cmd *cmd, t_iterator *iter)
{
	bool	is_expand;

	is_expand = true;
	parse_redir(exec, &cmd->redir[iter->redir_iter], iter);
	if (ft_realloc_array(&cmd->redir, iter->redir_iter + 1))
		ft_error(exec, "malloc error", MALLOC_ERROR);
	if (exec->token[iter->token_iter].type == SPACE_TOKEN)
		iter->token_iter = iter->token_iter + 1;
	if (exec->token[iter->token_iter].type == OPEN_DQUOTE_TOKEN)
		is_expand = false;
	parse_dquote(exec, &cmd->redir[iter->redir_iter], iter, false);
	heredoc(exec, &cmd->redir[iter->redir_iter], iter, is_expand);
	iter->redir_iter = iter->redir_iter + 1;
	iter->cmds_iter = iter->cmds_iter - 1;
}

static void	parser_loop( t_exec *exec, t_cmd *cmd, t_iterator *iter)
{
	if (exec->token[iter->token_iter].type != SPACE_TOKEN)
	{
		if (exec->token[iter->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(exec, &cmd->cmd[iter->cmds_iter], iter, true);
		else if (exec->token[iter->token_iter].type == OPEN_DQUOTE_TOKEN)
			parse_dquote(exec, &cmd->cmd[iter->cmds_iter], iter, 0);
		else if (is_redir(&exec->token[iter->token_iter]))
			parse_redir_and_filename(exec, cmd, iter);
		else
			parse_string(exec, &cmd->cmd[iter->cmds_iter], iter);
		iter->cmds_iter = iter->cmds_iter + 1;
		if (ft_realloc_array(&cmd->cmd, iter->cmds_iter + 1))
			ft_error(exec, "malloc error", MALLOC_ERROR);
		if (ft_realloc_array(&cmd->redir, iter->redir_iter + 1))
			ft_error(exec, "malloc error", MALLOC_ERROR);
	}
	else
		iter->token_iter = iter->token_iter + 1;
}

/* 
	iterates through the token array 
	and create simple command array splits on pipe	*/
void	parse(t_exec *exec)
{
	t_iterator	iter;

	init_data(exec, &iter);
	while (++iter.cmd_count < exec->cmd_count)
	{
		iter.cmds_iter = 0;
		iter.redir_iter = 0;
		exec->cmd[iter.cmd_count].redir = ft_calloc(2, sizeof(char *));
		if (exec->cmd[iter.cmd_count].redir == NULL)
			ft_error(exec, "malloc error", MALLOC_ERROR);
		exec->cmd[iter.cmd_count].cmd = ft_calloc(1, sizeof(char *));
		if (exec->cmd[iter.cmd_count].cmd == NULL)
			ft_error(exec, "malloc error", MALLOC_ERROR);
		while (exec->token[iter.token_iter].type != EOL_TOKEN
			&& exec->token[iter.token_iter].type != PIPE_TOKEN)
			parser_loop(exec, &exec->cmd[iter.cmd_count], &iter);
		exec->cmd[iter.cmd_count].cmd[iter.cmds_iter] = NULL;
		exec->cmd[iter.cmd_count].redir[iter.redir_iter] = NULL;
		if (exec->token[iter.token_iter].type == PIPE_TOKEN)
			iter.token_iter = iter.token_iter + 1;
	}
	exec->cmd[iter.cmd_count].cmd = NULL;
	exec->cmd[iter.cmd_count].redir = NULL;
}

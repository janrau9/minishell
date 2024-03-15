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

static void	parse_redir_and_filename(t_data *data, t_cmd *cmd, t_iterator *iter)
{
	parse_redir(data, &cmd->redir[iter->redir_iter], iter);
	if (ft_realloc_array(&cmd->redir, iter->redir_iter + 1))
		ft_error(data, "malloc error", MALLOC_ERROR);
	if (data->token[iter->token_iter].type == SPACE_TOKEN)
		iter->token_iter = iter->token_iter + 1;
	parse_dquote(data, &cmd->redir[iter->redir_iter], iter);
	iter->redir_iter = iter->redir_iter + 1;
	iter->cmds_iter = iter->cmds_iter - 1;
}

static void	parser_loop( t_data *data, t_cmd *cmd, t_iterator *iter)
{
	if (data->token[iter->token_iter].type != SPACE_TOKEN)
	{
		if (data->token[iter->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(data, &cmd->cmd[iter->cmds_iter], iter);
		else if (data->token[iter->token_iter].type == OPEN_DQUOTE_TOKEN)
			parse_dquote(data, &cmd->cmd[iter->cmds_iter], iter);
		else if (is_redir(&data->token[iter->token_iter]))
			parse_redir_and_filename(data, cmd, iter);
		else
			parse_string(data, &cmd->cmd[iter->cmds_iter], iter);
		iter->cmds_iter = iter->cmds_iter + 1;
		if (ft_realloc_array(&cmd->cmd, iter->cmds_iter + 1))
			ft_error(data, "malloc error", MALLOC_ERROR);
		if (ft_realloc_array(&cmd->redir, iter->redir_iter + 1))
			ft_error(data, "malloc error", MALLOC_ERROR);
	}
	else
		iter->token_iter = iter->token_iter + 1;
}

/* 
	iterates through the token array 
	and create simple command array splits on pipe	*/
void	parse(t_data *data)
{
	t_iterator	iter;

	init_data(data, &iter);
	while (++iter.cmd_count < data->exec.cmd_count)
	{
		iter.cmds_iter = 0;
		iter.redir_iter = 0;
		data->exec.cmd[iter.cmd_count].redir = ft_calloc(2, sizeof(char *));
		if (data->exec.cmd[iter.cmd_count].redir == NULL)
			ft_error(data, "malloc error", MALLOC_ERROR);
		data->exec.cmd[iter.cmd_count].cmd = ft_calloc(1, sizeof(char *));
		if (data->exec.cmd[iter.cmd_count].cmd == NULL)
			ft_error(data, "malloc error", MALLOC_ERROR);
		while (data->token[iter.token_iter].type != EOL_TOKEN
			&& data->token[iter.token_iter].type != PIPE_TOKEN)
			parser_loop(data, &data->exec.cmd[iter.cmd_count], &iter);
		data->exec.cmd[iter.cmd_count].cmd[iter.cmds_iter] = NULL;
		data->exec.cmd[iter.cmd_count].redir[iter.redir_iter] = NULL;
		if (data->token[iter.token_iter].type == PIPE_TOKEN)
			iter.token_iter = iter.token_iter + 1;
	}
	data->exec.cmd[iter.cmd_count].cmd = NULL;
	data->exec.cmd[iter.cmd_count].redir = NULL;
}

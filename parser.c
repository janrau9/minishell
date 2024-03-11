/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:48:54 by jberay            #+#    #+#             */
/*   Updated: 2024/03/11 09:45:14 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir(char **dst, t_data *data)
{
	ft_substr_custom(dst, data->read_line, \
	data->token[data->token_iter].location.start, \
	data->token[data->token_iter].location.len);
	data->token_iter = data->token_iter + 1;
	data->redir_iter = data->redir_iter + 1;

	ft_realloc_array(&data->cmd->redir, data->redir_iter + 1);

	if (data->token[data->token_iter].type == SPACE_TOKEN)
		data->token_iter = data->token_iter + 1;
	parse_dquote(&data->cmd->redir[data->redir_iter], data);
	data->redir_iter = data->redir_iter + 1;
	data->cmds_iter = data->cmds_iter - 1;
}

/*Malloc substring from char* start and len in t_token struct*/
void	parse_string(char **dst, t_data *data)
{
	ft_substr_custom(dst, data->read_line, \
	data->token[data->token_iter].location.start, \
	data->token[data->token_iter].location.len);
	data->token_iter = data->token_iter + 1;
}


/*Malloc substring and  expand $ variable*/
void	parse_dollar(char **dst, t_data *data)
{
	char			*env_str;
	char			*expand_str;

	ft_substr_custom(&env_str, data->read_line, \
	data->token[data->token_iter].location.start, \
	data->token[data->token_iter].location.len);
	expand_str = getenv(env_str);
	if (!expand_str)
		expand_str = "";
	*dst = ft_strdup(expand_str);
	free(env_str);
	data->token_iter = data->token_iter + 1;
}

/*
	** Malloc substring until space or EOL_TOKEN
	** str[0] = string result
	** str[1] = parsed string
	** str[2] = temporary string to free
	** iter[0] = iter to iterate through tokens
	** iter[1] = iter pointer to pass to functions
*/
void	parse_dquote(char **dst, t_data *data)
{
	size_t	quote;
	char	*str[3];

	quote = data->token_iter;
	str[0] = ft_strdup("");
	while (data->token[quote].type != EOL_TOKEN
		&& data->token[quote].type != SPACE_TOKEN
		&& data->token[quote].type != REDIR_APPEND_TOKEN
		&& data->token[quote].type != REDIR_IN_TOKEN
		&& data->token[quote].type != REDIR_OUT_TOKEN
		&& data->token[quote].type != REDIR_HEREDOC_TOKEN
		&& data->token[quote].type != PIPE_TOKEN)
		quote++;
	while (data->token_iter < quote)
	{
		str[2] = str[0];
		if (data->token[data->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(&str[1], data);
		else
			parse_string(&str[1], data);
		ft_strjoin_custom(&str[0], str[2], str[1]);
	}
	*dst = str[0];
}

void	parser_loop(t_cmd *cmd, t_data *data)
{
	if (data->token[data->token_iter].type != SPACE_TOKEN)
	{
		if (data->token[data->token_iter].type == DOLLAR_TOKEN)
			parse_dollar(&cmd->cmd[data->cmds_iter], data);
		else if (data->token[data->token_iter].type == OPEN_DQUOTE_TOKEN)
			parse_dquote(&cmd->cmd[data->cmds_iter], data);
		else if (data->token[data->token_iter].type == REDIR_APPEND_TOKEN
			|| data->token[data->token_iter].type == REDIR_IN_TOKEN
			|| data->token[data->token_iter].type == REDIR_OUT_TOKEN
			|| data->token[data->token_iter].type == REDIR_HEREDOC_TOKEN)
		{
			data->cmd = cmd;
			parse_redir(&cmd->redir[data->redir_iter], data);
		}
		else
			parse_string(&cmd->cmd[data->cmds_iter], data);
		data->cmds_iter = data->cmds_iter + 1;
		ft_realloc_array(&cmd->cmd, data->cmds_iter + 1);
		ft_realloc_array(&cmd->redir, data->redir_iter + 1);
	}
	else
		data->token_iter = data->token_iter + 1;
}

void init_data(t_data *data, char *read_line)
{
	size_t	i;
	size_t	pipe_count;

	data->token_iter = 0;
	data->read_line = read_line;
	i = 0;
	pipe_count = 0;
	while (data->token[i].type != EOL_TOKEN)
	{
		if (data->token[i].type == PIPE_TOKEN)
			pipe_count++;
		i++;
	}
	data->pipe_count = pipe_count;
}

/*iterates through the token array and create simple command array splits on pipe*/
void	parse(t_cmd **cmd_arr, t_data *data, char *read_line)
{
	size_t	cmd_count;
	t_cmd	*cmd;

	cmd = *cmd_arr;
	init_data(data, read_line);
	cmd = ft_calloc(data->pipe_count + 2, sizeof(t_cmd));
	cmd_count = 0;
	while (cmd_count < data->pipe_count + 1)
	{
		data->cmds_iter = 0;
		data->redir_iter = 0;
		cmd[cmd_count].redir = ft_calloc(2, sizeof(char *));
		cmd[cmd_count].cmd = ft_calloc(1, sizeof(char *));
		while (data->token[data->token_iter].type != EOL_TOKEN
			&& data->token[data->token_iter].type != PIPE_TOKEN)
			parser_loop(&cmd[cmd_count], data);
		cmd[cmd_count].cmd[data->cmds_iter] = NULL;
		cmd[cmd_count].redir[data->redir_iter] = NULL;
		if (data->token[data->token_iter].type == PIPE_TOKEN)
			data->token_iter = data->token_iter + 1;
		cmd_count++;
	}
	cmd[cmd_count].cmd = NULL;
	cmd[cmd_count].redir = NULL;
	*cmd_arr = cmd;
}

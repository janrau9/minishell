/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 08:54:07 by jberay            #+#    #+#             */
/*   Updated: 2024/03/15 08:55:46 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	re_promt(t_data *data)
{
	char	*read_line_new;
	char	*rd_space;
	//int 	fda;
	int 	fd_og = dup(STDIN_FILENO);

/* 	open("a.txt", O_CREAT | O_RDONLY);
	fda = open ("a.txt", O_CREAT | O_EXCL);
	if (fda == -1)
		close (STDIN_FILENO); */
	read_line_new = readline("> ");
	if (!read_line_new && g_in_reprompt)
	{
		dup2(fd_og, STDIN_FILENO);
		return (UNEXPECTED_EOF);
	}
	if (!read_line_new)
	{
		g_in_reprompt = 1;
		return (UNEXPECTED_EOF);
	}
	if (!*read_line_new)
		return (0);
	rd_space = ft_strjoin(data->read_line, " ");
	if (!rd_space)
		return (MALLOC_ERROR);
	free(data->read_line);
	ft_strjoin_custom(&data->read_line, rd_space, read_line_new);
	if (!data->read_line)
	{
		free(rd_space);
		free(read_line_new);
		return (MALLOC_ERROR);
	}
	add_history(data->read_line);
	return (0);
}

int	check_command_after_pipe(t_data *data)
{
	size_t	i;
	int		cmd_flag;
	int		err_return;

	cmd_flag = 0;
	while (cmd_flag == 0)
	{
		err_return = tokenizer(data);
		if (err_return)
			return (err_return);
		i = ft_strlen(data->read_line);
		while (data->read_line[--i] != '|' && i > 0)
		{
			if (data->read_line[i] != ' ' && data->read_line[i] != '|')
				cmd_flag = 1;
		}
		if (cmd_flag == 0)
		{
			err_return = re_promt(data);
			if (err_return)
				return (err_return);
			free(data->token);
		}
	}
	return (0);
}
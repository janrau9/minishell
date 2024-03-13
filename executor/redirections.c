/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:31:06 by jtu               #+#    #+#             */
/*   Updated: 2024/03/13 19:14:42 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_outfile(char *redir, char *file)
{
	int	fd_out;

	if (ft_strncmp(redir, ">>", 3))
		fd_out = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd_out = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0)
		error_exit(OPEN_FAIL, file);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		error_exit(DUP_FAIL, NULL);
	close(fd_out);
}

void	handle_infile(char *file)
{
	int	fd_in;

	fd_in = open(file, O_RDONLY);
	if (fd_in < 0)
		error_exit(OPEN_FAIL, file);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		error_exit(DUP_FAIL, NULL);
	close(fd_in);
}

void	check_redirections(t_cmd *parsed_cmd)
{
	int	i;
	int	j;

	j = 0;
	while (parsed_cmd[j].cmd != NULL)
	{
		i = 0;
		while (parsed_cmd[j].redir[i] != NULL)
		{
			if (ft_strncmp(parsed_cmd[j].redir[i], "<", 2) || ft_strncmp(parsed_cmd[j].redir[i], "<<", 3))
			{
				handle_infile(parsed_cmd[j].redir[i + 1]);
			}
			if (ft_strncmp(parsed_cmd[j].redir[i], ">", 2) || ft_strncmp(parsed_cmd[j].redir[i], ">>", 3))
			{
				handle_outfile(parsed_cmd[j].redir[i], parsed_cmd[j].redir[i + 1]);
			}
			i++;
		}
		j++;
	}
}

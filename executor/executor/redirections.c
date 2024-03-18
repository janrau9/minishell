/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:31:06 by jtu               #+#    #+#             */
/*   Updated: 2024/03/14 13:06:33 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_outfile(char *redir, char *file)
{
	int	fd_out;

	if (!ft_strncmp(redir, ">>", 3))
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

void	check_redirections(t_cmd parsed_cmd)
{
	int	i;

	i = 0;
	// ft_putendl_fd(parsed_cmd.redir[i], STDERR_FILENO);
	// if(!ft_strncmp(parsed_cmd.redir[i], "<", 2))
	// 	ft_putendl_fd("no difference", STDERR_FILENO);
	while (parsed_cmd.redir[i] != NULL)
	{
		if (!ft_strncmp(parsed_cmd.redir[i], "<", 2) || !ft_strncmp(parsed_cmd.redir[i], "<<", 3))
		{
			// ft_putendl_fd("infile", STDERR_FILENO);
			handle_infile(parsed_cmd.redir[i + 1]);
		}
		if (!ft_strncmp(parsed_cmd.redir[i], ">", 2) || !ft_strncmp(parsed_cmd.redir[i], ">>", 3))
		{
			// ft_putendl_fd("outfile", STDERR_FILENO);
			handle_outfile(parsed_cmd.redir[i], parsed_cmd.redir[i + 1]);
		}
		i++;
	}
}

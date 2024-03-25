/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:32:17 by jtu               #+#    #+#             */
/*   Updated: 2024/03/25 13:20:12 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../libft/libft.h"
// # include "../minishell.h"
# include <fcntl.h>

// typedef struct s_cmd
// {
// 	char	**cmd;
// 	char	**redirection;
// }	t_cmd;

// typedef struct s_util
// {
// 	bool	here_doc;
// 	int		pipes;
// 	int		exit_code;
// }	t_util;

# define RD 0
# define WR 1

typedef enum s_error
{
	NO_ERROR,
	WRONG_ARGC,
	PIPE_FAIL,
	FORK_FAIL,
	DUP_FAIL,
	OPEN_FAIL,
	MALLOC_FAIL,
	STAT_FAIL,
	WRONG_FILE,
	CMD_NOT_FOUND,
	NO_PATH,
	NO_PERMISSION,
	EXECVE_FAIL,
	IS_DIR,
}	t_error;

// void	executor(t_cmd *parsed_cmd, t_util *util, char **envp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:32:17 by jtu               #+#    #+#             */
/*   Updated: 2024/03/07 19:27:47 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../libft/libft.h"
# include "../minishell.h"

typedef struct s_cmd
{
	char	**cmd;
	char	**redirection;
}	t_cmd;

typedef struct s_util
{
	bool	here_doc;
	int		pipes;
	int		exit_code;
}	t_util;

#endif
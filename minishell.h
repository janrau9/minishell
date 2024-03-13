/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:13:23 by jberay            #+#    #+#             */
/*   Updated: 2024/03/13 14:04:08 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "token.h"
# include "parser.h"
# include "char_iter.h"
# include <fcntl.h>

# include <signal.h>
# include <termios.h>

typedef struct s_cmd
{
	char	**cmd;
	char	**redir;
}	t_cmd;

typedef struct s_data
{
	char	*read_line;
	t_token	*token;
	size_t	token_iter;
	size_t	cmds_iter;
	size_t	redir_iter;
	size_t	pipe_count;
}	t_data;

typedef struct s_exec
{
	t_cmd	*cmd;
	size_t	cmd_count;
	char	**envp;
	int		exit_code;
}	t_exec;


void	rl_replace_line(const char *text, int clear_undo);

/* parser */
void	parse(t_cmd **cmd, t_data *data);

void	parse_redir(char **dst, t_data *data);
void	parse_string(char **dst, t_data *data);
void	parse_dollar(char **dst, t_data *data);
void	parse_dquote(char **dst, t_data *data);
void	init_data(t_data *data);

bool	is_redir(t_token *token);

void	builtin(t_exec *exec);
void	ft_export(t_exec *exec);
size_t	ft_arrlen(char **arr);
void	ft_arrdup(char ***dst_add, char **src);
void	ft_arrcpy(char ***dst_add, char **src);

void	ft_freearr(char ***array);
#endif
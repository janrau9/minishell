/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:13:23 by jberay            #+#    #+#             */
/*   Updated: 2024/03/14 14:57:53 by jberay           ###   ########.fr       */
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
# include "executor/executor.h"
# include <fcntl.h>

# include <signal.h>
# include <termios.h>

typedef struct s_cmd
{
	char	**cmd;
	char	**redir;
}	t_cmd;

typedef struct s_exec
{
	t_cmd	*cmd;
	char	**envp;
	int		exit_code;
	size_t	pipe_count;
	size_t	cmd_count;
	int		*pid;
}	t_exec;

typedef struct s_data
{
	char	*read_line;
	t_token	*token;
	t_exec	exec;
	size_t	token_iter;
	size_t	cmds_iter;
	size_t	redir_iter;
	int		shell_status;
}	t_data;

typedef enum e_error_code
{
	NO_ERR,
	MALLOC_ERROR = -1,
	NULL_ERROR = -2,
	SYNTAX_ERROR = 258,
	UNEXPECTED_EOF = 258,
}	t_error_code;

/* token */

int		tokenizer(t_data *data);

void	rl_replace_line(const char *text, int clear_undo);

/* parser */
void	parse(t_data *data);

void	parse_redir(char **dst, t_data *data);
void	parse_string(char **dst, t_data *data);
void	parse_dollar(char **dst, t_data *data);
void	parse_dquote(char **dst, t_data *data);
void	init_data(t_data *data);

bool	is_redir(t_token *token);

void	builtin(t_data *data);
void	ft_export(t_exec *exec);

/*Array utils*/
size_t	ft_arrlen(char **arr);
int		ft_arrdup(char ***dst_add, char **src);
void	ft_arrcpy(char ***dst_add, char **src);
void	ft_freearr(char ***array);
void	ft_realloc_array(t_data *data, char ***args, size_t size);

int		ft_error(t_data *data, char *msg, int return_code);

//exector
void	executor(t_exec *exec);
void	error_exit(t_error error, char *s);
void	free_arr(char **arr);
void	error_free_exit(char **s);
void	check_redirections(t_cmd parsed_cmd);
void	check_buildins(char **cmd, char **envp);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:13:23 by jberay            #+#    #+#             */
/*   Updated: 2024/03/18 11:17:48 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "token.h"
# include "parser.h"
# include "char_iter.h"
# include "executor/executor.h"


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
	size_t	cmd_count;
	char	**envp;
	int		exit_code;
	int		*pid;
}	t_exec;

typedef struct s_data
{
	char	*read_line;
	t_token	*token;
	t_exec	exec;
	// size_t	token_iter;
	// size_t	cmds_iter;
	// size_t	redir_iter;
}	t_data;

typedef enum e_error_code
{
	NO_ERR,
	FORK_ERROR,
	MALLOC_ERROR = -1,
	NULL_ERROR = -2,
	SYNTAX_ERROR = 258,
	UNEXPECTED_EOF = 258,
}	t_error_code;

extern unsigned int	g_in_reprompt;
/*minishell*/
void	heredoc(t_data *data);
void	togglesignal(int mode);
void	signal_handler(int signum);

/*minishell utils*/
void	rl_replace_line(const char *text, int clear_undo);

int		check_command_after_pipe(t_data *data);


/* token */
int		tokenizer(t_data *data);



/* parser */
void	parse(t_data *data);
void	parse_redir(t_data *data, char **dst, t_iterator *iter);
void	parse_string(t_data *data, char **dst, t_iterator *iter);
void	parse_dollar(t_data *data, char **dst, t_iterator *iter);
void	parse_dquote(t_data *data, char **dst, t_iterator *iter);
void	init_data(t_data *data, t_iterator *iter);
/*parser utils*/
bool	is_redir(t_token *token);

void	builtin(t_data *data);
void	ft_export(t_exec *exec);

/*Array utils*/
size_t	ft_arrlen(char **arr);
int		ft_arrdup(char ***dst_add, char **src);
void	ft_arrcpy(char ***dst_add, char **src);
int		ft_realloc_array(char ***dst_add, size_t size);
/*frees*/
void	ft_freearr(char ***array_add);
void	ft_freestruct(t_cmd **cmd);
void	ft_freeall(t_data *data);

int		ft_error(t_data *data, char *msg, int return_code);

//exector
void	executor(t_data *data);
void	error_exit(t_error error, char *s);
void	free_arr(char **arr);
void	error_free_exit(char **s);
void	check_redirections(t_cmd parsed_cmd);
void	check_buildins(char **cmd, char **envp);
void	ft_unset(t_exec *exec);
void	ft_cd(char **cmd, char **envp);

#endif
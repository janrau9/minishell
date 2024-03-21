/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:13:23 by jberay            #+#    #+#             */
/*   Updated: 2024/03/21 10:40:17 by jberay           ###   ########.fr       */
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
	char	*read_line;
	t_token	*token;
	t_cmd	*cmd;
	size_t	cmd_count;
	char	**envp;
	int		exit_code;
	int		*pid;
}	t_exec;

/* typedef struct s_exec
{
	char	*read_line;
	t_token	*token;
	t_exec	exec;
	// size_t	token_iter;
	// size_t	cmds_iter;
	// size_t	redir_iter;
}	t_exec; */

typedef enum e_error_code
{
	NO_ERR,
	FORK_ERROR,
	MALLOC_ERROR = -1,
	NULL_ERROR = -2,
	SYNTAX_ERROR = 258,
	UNEXPECTED_EOF = 258,
}	t_error_code;

typedef struct s_global
{
	int	in_heredoc;
	int	in_reprompt;
}	t_global;

t_global	g;

/*minishell*/
int		heredoc(t_exec *exec, char **dst, t_iterator *iter, bool is_expand);
void	write_to_heredoc(t_exec *exec, int fd, \
char *delimiter, int is_expand);

/*minishell utils*/
void	prep_for_promt(t_exec *exec);
void	prompt(t_exec *exec);

void	rl_replace_line(const char *text, int clear_undo);
void	initialize_exec(t_exec *exec);
int		check_command(t_exec *exec);

/*signals*/
void	enablerawmode(void);
void	togglesignal(int mode);
void	signal_handler(int signum);



/* token */
void	tokenizer(t_exec *exec);


/* parser */
int		parse(t_exec *exec);
void	parse_redir(t_exec *exec, char **dst, t_iterator *iter);
void	parse_string(t_exec *exec, char **dst, t_iterator *iter);
void	parse_dollar(t_exec *exec, char **dst, \
t_iterator *iter, bool is_expand);
void	parse_dquote(t_exec *exec, char **dst, \
t_iterator *iter, bool is_expand);
void	init_data(t_exec *exec, t_iterator *iter);
/*parser utils*/
bool	is_redir(t_token *token);

void	builtin(t_exec *exec);
int		ft_export(t_exec *exec);

/*Array utils*/
size_t	ft_arrlen(char **arr);
int		ft_arrdup(char ***dst_add, char **src);
void	ft_arrcpy(char ***dst_add, char **src);
int		ft_realloc_array(char ***dst_add, size_t size);
/*frees*/
void	ft_freearr(char ***array_add);
void	ft_freestruct(t_cmd **cmd);
void	ft_freeall(t_exec *exec);
void	ft_freeall_n_envp(t_exec *exec);

int		ft_error(t_exec *exec, char *msg, int return_code);

//exector
void	executor(t_exec *exec);
void	error_exit(t_error error, char *s);
void	free_arr(char **arr);
void	error_free_exit(char **s);
void	check_redirections(t_cmd parsed_cmd);
void	check_buildins(char **cmd, char **envp);


/*debug*/
void	token_print(t_token *token);
void	print_array(char **array);
void	print_cmd(t_cmd **cmd_ptr);
#endif
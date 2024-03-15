/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:53:49 by jberay            #+#    #+#             */
/*   Updated: 2024/03/15 14:41:52 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// typedef enum e_node_type
// {
// 	STRING_NODE,
// 	PIPE_NODE,
// 	REDIR_IN_NODE,
// 	REDIR_OUT_NODE,
// 	REDIR_APPEND_NODE,
// 	REDIR_HEREDOC_NODE,
// 	ERROR_NODE,
// }	t_node_type;

// typedef char		*t_string_value;
// typedef char		*t_pipe_value;
// typedef char		*t_redir_in_value;
// typedef char		*t_redir_out_value;
// typedef char		*t_redir_append_value;
// typedef char		*t_redir_heredoc_value;
// typedef char		*t_error_value;

// typedef union u_node_value
// {
// 	t_string_value			string_value;
// 	t_pipe_value			pipe_value;
// 	t_redir_in_value		redir_in_value;
// 	t_redir_out_value		redir_out_value;
// 	t_redir_append_value	redir_append_value;
// 	t_redir_heredoc_value	redir_heredoc_value;
// 	t_error_value			error_value;
// }	t_node_value;

// typedef struct s_node
// {
// 	t_node_type		type;
// 	t_node_value	value;
// }	t_node;

typedef struct s_iterator
{
	size_t	token_iter;
	size_t	cmds_iter;
	size_t	redir_iter;
	size_t	cmd_count;
}	t_iterator;


/*parser utils*/
int		ft_substr_custom(char **dst, char const *s, char *start, size_t len);
int		ft_strjoin_custom(char **dst, char *s1, char *s2);

/*debug*/
void	token_print(t_token *token);
#endif
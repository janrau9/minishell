/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 08:34:25 by jberay            #+#    #+#             */
/*   Updated: 2024/03/05 08:59:30 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/*
	RULES

	node = arr str
	arr str = cmd and arg | redir
	string
	
	array of strings = terminal
	$expansion = terminal
	< | > | >> | << = array of strings
	command = array of strings
	args = array of strings
	double quotes = $expansion | command | args
	single quotes = command | args
	
	NODE
		node type - enum of token nodes
		node data - union of token data
*/

typedef enum e_node_type
{
	ERROR_NODE,
	ARR_STR_NODE,
	DOLLAR_NODE,
	REDIR_NODE,
	CMD_ARGS_NODE,
	DOUBLEQ_NODE,
	SINGGLEQ_NODE,
}	t_node_type;

typedef struct nod	t_node;

typedef struct quote_value
{
	t_node			*quote_value;
}	t_quote_value;


typedef char		*t_error_value;
typedef char		*t_cmd_value; // cmd string
typedef char		*t_args_value; // args string
typedef char		*t_dollar_value;
typedef char		**t_redir_value;

typedef union u_node_value
{
	t_error_value	error_value;
	t_cmd_value		cmd_value;
	t_args_value	args_value;
	t_dollar_value	dollar_value;
	t_redir_value	redir_value;
	t_quote_value	double_value;
	t_quote_value	single_value;
}	t_node_value;

typedef struct s_node
{
	t_node_type		type;
	t_node_value	value;
}	t_node;

/*parsing
* tokens
	* |
		- pipe
	* open double quotes
		- if first char is double quote.
		- if quote - 1 is space
		* data
			- string
			- $ expansion
		* error
			- if no closing quote
	* single quotes
		- if first char is single quote.
		- if quote - 1 is space
		* data
			- string
		* error
			- if no closing quote
	* < redirection
		* data next string is infile name
	* > redirection
		* next string is outfile name
	* >> append mode
		* next string is outfile name append
	* << heredoc
	* $ expansion
		* next string is env variable
	* $
		* exit status
*/

#endif
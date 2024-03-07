/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:53:49 by jberay            #+#    #+#             */
/*   Updated: 2024/03/07 11:31:50 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token_iter.h"

void	parse_string(char **dst, t_token **token, \
char *read_line, t_token_iter *iter_ptr);
void	parse_dollar(char **dst, t_token **token, \
char *read_line, t_token_iter *iter_ptr);
void	parse_dquote(char **dst, t_token **token, \
char *read_line, t_token_iter *iter_ptr);

#endif
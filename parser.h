/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:53:49 by jberay            #+#    #+#             */
/*   Updated: 2024/03/08 12:36:09 by jberay           ###   ########.fr       */
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


/*parser utils*/
void	ft_realloc_array(char ***args, size_t size);
int		ft_substr_custom(char **dst, char const *s, char *start, size_t len);
int		ft_strjoin_custom(char **dst, char *s1, char *s2);

/*debug*/
void	token_print(t_token *token);
#endif
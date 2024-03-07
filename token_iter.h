/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_iter.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:25:34 by jberay            #+#    #+#             */
/*   Updated: 2024/03/06 10:04:33 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_ITER_H
# define TOKEN_ITER_H

# include "token.h"
# include "char_iter.h"

typedef struct s_token_iter
{
	t_token		*start;
	t_token		*end;
}	t_token_iter;

t_token_iter	token_iter_value(t_token *self, size_t len);
bool			token_iter_has_next(t_token_iter *self);
void			token_iter_next(t_token_iter *self);
t_token_type	token_iter_peek(t_token_iter *self);

#endif
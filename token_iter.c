/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:24:18 by jberay            #+#    #+#             */
/*   Updated: 2024/03/06 10:46:40 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_iter.h"

t_token_iter	token_iter_value(t_token *self, size_t len)
{
	t_token_iter	iter;

	iter.start = self;
	iter.end = self + len;
	return (iter);

}

bool	token_iter_has_next(t_token_iter *self)
{
	bool	has_next;

	has_next = false;
	if (self->start + 1 != self->end)
		has_next = true;
	return (has_next);
}

void	token_iter_next(t_token_iter *self)
{
	self->start++;
}

t_token_type	token_iter_peek(t_token_iter *self)
{
	return (self->start->type);
}
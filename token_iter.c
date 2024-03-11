/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:24:18 by jberay            #+#    #+#             */
/*   Updated: 2024/03/08 09:16:06 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_iter.h"

t_token_iter	token_iter_value(t_token *self, t_token_type type)
{
	t_token_iter	iter;
	size_t			size;

	size = 0;
	while (self[size].type != type)
		size++;
	iter.start = self;
	iter.end = self + size;
	return (iter);
}

t_token	*token_iter_cursor(t_token_iter *self)
{
	return (self->start);
}

t_token	*token_iter_find(t_token *self, t_token_type type)
{
	t_token_iter	iter;

	iter = token_iter_value(self, type);
	return (iter.end);
}

void	token_iter_next(t_token_iter *self)
{
	self->start++;
}

t_token_type	token_iter_peek(t_token_iter *self)
{
	return (self->start->type);
}
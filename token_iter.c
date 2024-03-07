/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:24:18 by jberay            #+#    #+#             */
/*   Updated: 2024/03/07 13:59:56 by jberay           ###   ########.fr       */
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

t_token	*token_iter_cursor(t_token_iter *self)
{
	return (self->start);
}

t_token	*token_iter_find(t_token *self, t_token_type type)
{
	size_t			size;
	t_token_iter	iter;

	size = 0;
	while (self[size].type != type)
		size++;
	iter = token_iter_value(self, size);
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
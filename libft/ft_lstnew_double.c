/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:38:09 by jberay            #+#    #+#             */
/*   Updated: 2024/03/08 14:13:59 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_lstnew_double(void *content)
{
	t_dlist	*plst;

	plst = malloc(sizeof(t_dlist));
	if (!plst)
		return (NULL);
	plst->content = content;
	plst->next = NULL;
	plst->prev = NULL;
	return (plst);
}

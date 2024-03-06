/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:38:09 by jberay            #+#    #+#             */
/*   Updated: 2023/11/06 11:00:35 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*plst;

	plst = malloc(sizeof(t_list));
	if (!plst)
		return (NULL);
	plst->content = content;
	plst->next = NULL;
	return (plst);
}

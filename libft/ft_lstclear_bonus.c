/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:59:58 by jberay            #+#    #+#             */
/*   Updated: 2023/11/02 13:59:59 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*temp;

	if (lst && del)
	{
		ptr = *lst;
		while (ptr != NULL)
		{
			temp = ptr;
			ptr = ptr->next;
			del(temp->content);
			free(temp);
		}
		*lst = NULL;
	}
}

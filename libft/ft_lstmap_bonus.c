/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:10:15 by jberay            #+#    #+#             */
/*   Updated: 2023/11/06 11:19:42 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*head;
	void	*c;

	if (lst)
	{
		head = NULL;
		while (lst)
		{
			c = f(lst->content);
			temp = ft_lstnew(c);
			if (!temp)
			{
				del(c);
				ft_lstclear(&head, del);
				return (NULL);
			}
			ft_lstadd_back(&head, temp);
			lst = lst->next;
		}
		return (head);
	}
	return (NULL);
}

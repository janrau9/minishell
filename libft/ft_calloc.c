/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 07:59:30 by jberay            #+#    #+#             */
/*   Updated: 2023/11/01 16:59:20 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count != 0 && (SIZE_MAX / count < size))
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:04:08 by jberay            #+#    #+#             */
/*   Updated: 2023/11/01 16:27:26 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;
	size_t	h;

	if ((needle[0] == '\0'))
		return ((char *)haystack);
	if ((!haystack || !needle) && len == 0)
		return (0);
	h = 0;
	while (haystack[h] && h < len)
	{
		n = 0;
		while ((haystack[h + n] == needle[n])
			&& h + n < len && needle[n])
			n++;
		if (needle[n] == 0)
			return (&((char *)haystack)[h]);
		h++;
	}
	return (NULL);
}

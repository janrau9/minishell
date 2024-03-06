/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:03:45 by jberay            #+#    #+#             */
/*   Updated: 2023/11/01 08:03:47 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	slen;
	size_t	tlen;

	i = 0;
	slen = ft_strlen(s);
	tlen = slen;
	while (i < tlen +1)
	{
		if (s[slen] == (char)c)
			return (&((char *)s)[slen]);
		i++;
		slen--;
	}
	return (0);
}

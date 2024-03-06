/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:53:43 by jberay            #+#    #+#             */
/*   Updated: 2024/03/06 12:31:45 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if ((size_t)start >= slen)
		len = 0;
	if (slen - (size_t)start < len)
		len = slen - (size_t)start;
	ptr = malloc((len +1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memmove(ptr, &s[start], len);
	ptr[len] = 0;
	return (ptr);
}

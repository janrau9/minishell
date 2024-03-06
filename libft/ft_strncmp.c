/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:04:42 by jberay            #+#    #+#             */
/*   Updated: 2023/11/01 08:04:44 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	i = 0;
	if (n != 0)
	{
		while (ps1[i] == ps2[i] && ps1[i] && ps2[i] && i < n)
			i++;
		if (i == n)
			return (ps1[i -1] - ps2[i -1]);
		else
			return (ps1[i] - ps2[i]);
	}
	return (0);
}

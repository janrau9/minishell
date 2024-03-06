/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:46:43 by jberay            #+#    #+#             */
/*   Updated: 2023/11/01 15:52:42 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_set(const char *set, char c);

char	*ft_strtrim(char const *s1, const char *set)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	while (is_set(set, s1[i]) == 1)
		i++;
	while (s1[i] && (is_set(set, s1[len -1]) == 1))
		len--;
	ptr = malloc(len - i + 1);
	if (!ptr)
		return (0);
	ft_memmove(ptr, &s1[i], len - i);
	ptr[len - i] = 0;
	return (ptr);
}

static int	is_set(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

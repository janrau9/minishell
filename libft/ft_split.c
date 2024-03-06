/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:07:18 by jberay            #+#    #+#             */
/*   Updated: 2023/11/08 09:37:26 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**clear_array(char **s, size_t j)
{
	while (j > 0)
	{
		free(s[j -1]);
		j--;
	}
	free(s);
	return (NULL);
}

static char	**word_split(char **arr, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = 0;
			while ((s[i + len] != c) && s[i + len] != '\0')
				len++;
			arr[j] = ft_substr(s, i, len);
			if (!arr[j])
				return (clear_array(arr, j));
			i = i + len;
			j++;
		}
		else
			i++;
	}
	arr[j] = 0;
	return (arr);
}

static size_t	word_count(char const *s, char c)
{
	int		flag;
	size_t	count;
	int		i;

	flag = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c && flag == 1)
			flag = 0;
		i++;
	}
	return (count);
}

/**
 * @brief divide string into double array with the given delimiter
 * 
 * @param s string
 * @param c delimeter
 * @return char** 
 */
char	**ft_split(char const *s, char c)
{
	char	**mptr;

	if (!s)
		return (NULL);
	mptr = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!mptr)
		return (0);
	if (!word_split(mptr, s, c))
		return (NULL);
	return (mptr);
}

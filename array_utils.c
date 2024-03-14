/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 08:32:34 by jberay            #+#    #+#             */
/*   Updated: 2024/03/14 11:14:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_freearr(char ***array)
{
	size_t	i;
	char	**tmp;

	i = 0;
	if (!*array || !array)
		return ;
	tmp = *array;
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	*array = NULL;
}

int	ft_arrdup(char ***dst_add, char **src)
{
	size_t	src_size;
	size_t	i;
	char	**dst;

	if (!src)
		return (NULL_ERROR);
	src_size = ft_arrlen(src);
	dst = ft_calloc(src_size + 1, sizeof(char *));
	if (!dst)
		return (MALLOC_ERROR);
	i = 0;
	while (i < src_size)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			ft_freearr(&dst);
			return (MALLOC_ERROR);
		}
		i++;
	}
	dst[i] = NULL;
	*dst_add = dst;
	return (NO_ERROR);
}

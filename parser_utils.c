/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:03:58 by jberay            #+#    #+#             */
/*   Updated: 2024/03/11 10:05:29 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_realloc_array(char ***args, size_t size)
{
	char		**new;
	char		**tmp;
	size_t 		s;
	size_t		i;

	tmp = *args;
	new = ft_calloc(size, sizeof(char *));
	if (!new)
	{
		printf("Error with malloc\n");
		s = 0;
		while(tmp[s])
		{
			free(tmp[s]);
			s++;
		}
		free(tmp);
		exit(1);
	}
	i = 0;
	while (i < size)
	{
		new[i] = tmp[i];
		i++;
	}
	free(tmp);
	*args = new;
}

int	ft_substr_custom(char **dst, char const *s, char *start, size_t len)
{
	char	*ptr;

	if (!s || !start)
		return (-1);
	ptr = malloc((len +1) * sizeof(char));
	if (ptr == NULL)
		return (-1);
	ft_memcpy(ptr, start, len);
	ptr[len] = 0;
	*dst = ptr;
	return (0);
}

int	ft_strjoin_custom(char **dst, char *s1, char *s2)
{
	size_t	flen;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	flen = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(flen +1);
	if (!ptr)
		return (-1);
	ft_memmove(ptr, s1, ft_strlen(s1));
	ft_memmove(ptr + ft_strlen(s1), s2, ft_strlen(s2));
	ptr[flen] = 0;
	free(s1);
	free(s2);
	*dst = ptr;
	return (0);
}

void	token_print(t_token *token)
{
	size_t	i;

	i = 0;
	printf("Printing token array\n");
	while (token[i].type != EOL_TOKEN)
	{
		printf("token typ[%zu]:%d\n", i, token[i].type);
		printf("token len[%zu]:%zu\n", i, token[i].location.len);
		printf("token sta[%zu]:%s\n", i, token[i].location.start);
		i++;
	}
}
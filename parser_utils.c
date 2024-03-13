/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:12:01 by jberay            #+#    #+#             */
/*   Updated: 2024/03/13 15:08:08 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_realloc_array(char ***args, size_t size)
{
	char	**new;
	char	**tmp;
	size_t	i;

	tmp = *args;
	i = 0;
	new = ft_calloc(size, sizeof(char *));
	if (!new)
	{
		while (tmp[i])
		{
			free(tmp[i]);
			i++;
		}
		free(tmp);
		exit(1);
	}
	i = 0;
	while (i < size - 1)
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

void	init_data(t_data *data)
{
	size_t	i;
	size_t	pipe_count;

	data->token_iter = 0;
	i = 0;
	pipe_count = 0;
	while (data->token[i].type != EOL_TOKEN)
	{
		if (data->token[i].type == PIPE_TOKEN)
			pipe_count++;
		i++;
	}
	data->pipe_count = pipe_count;
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

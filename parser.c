/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:48:54 by jberay            #+#    #+#             */
/*   Updated: 2024/03/06 15:13:55 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_realloc_array(char ***args, size_t size)
{
	char		**new;
	char		**tmp;
	size_t		i;

	tmp = *args;
	new = malloc(sizeof(char *) * (size));
	if (!new)
	{
		printf("Error with malloc\n");
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

	if (!s || !start || len == 0)
		return (-1);
	ptr = malloc((len +1) * sizeof(char));
	if (ptr == NULL)
		return (-1);
	ft_memcpy(ptr, start, len);
	ptr[len] = 0;
	*dst = ptr;
	return (0);
}

int	expand_env(char **dst, char *read_line, t_token *token)
{
	char	*env;
	char	*expand;

	ft_substr_custom(&env, read_line, \
	token->location.start, token->location.len);
	expand = getenv(env);
	if (!expand)
		expand = "";
	*dst = ft_strdup(expand);
	free(env);
	return (0);
}

void	parse(char *read_line, t_token **token_ptr_add)
{
	size_t			i;
	size_t			size;
	t_token			*token;
	char			**args;

	token = *token_ptr_add;
	args = ft_calloc(1, sizeof(char *));
	token = *token_ptr_add;
	i = 0;
	size = 0;
	while (token[i].type != EOL_TOKEN)
	{
		if (token[i].location.len > 0)
		{
			if (token[i].type == DOLLAR_TOKEN)
				expand_env(&args[size], read_line, &token[i]);
			else
				ft_substr_custom(&args[size], read_line, \
				token[i].location.start, token[i].location.len);
			size++;
			ft_realloc_array(&args, size + 1);
		}
		i++;
	}
	args[size] = NULL;
	size = 0;
	while (args[size] != 0)
	{
		printf("args[%zu]:%s\n", size, args[size]);
		size++;
	}
	printf("args[%zu]:%s\n", size, args[size]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:48:54 by jberay            #+#    #+#             */
/*   Updated: 2024/03/07 14:47:52 by jberay           ###   ########.fr       */
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
	while (token[i].type != EOL_TOKEN)
	{
		printf("token[%zu]:%d\n", i, token[i].type);
		printf("token[%zu]:%zu\n", i, token[i].location.len);
		printf("token[%zu]:%s\n", i, token[i].location.start);
		i++;
	}
}

void	parse_string(char **dst, t_token **token_ptr_add, \
char *read_line, t_token_iter *iter_ptr)
{
	t_token			*token;
	t_token_iter	*iter;

	token = *token_ptr_add;
	iter = iter_ptr;
	ft_substr_custom(dst, read_line, \
	token->location.start, token->location.len);
	token_iter_next(iter_ptr);
	iter_ptr = iter;
}

void	parse_dollar(char **dst, t_token **token_ptr_add, \
char *read_line, t_token_iter *iter_ptr)
{
	char			*env_str;
	char			*expand_str;
	t_token			*token;
	t_token_iter	*iter;

	token = *token_ptr_add;
	iter = iter_ptr;
	ft_substr_custom(&env_str, read_line, \
	token->location.start, token->location.len);
	expand_str = getenv(env_str);
	if (!expand_str)
		expand_str = "";
	*dst = ft_strdup(expand_str);
	free(env_str);
	token_iter_next(iter);
	iter_ptr = iter;
}

/*
	** str[0] = string result
	** str[1] = parsed string
	** str[2] = temporary string to free
*/

void	parse_dquote(char **dst, t_token **token_ptr_add, \
char *read_line, t_token_iter *iter_ptr)
{
	t_token			*token;
	t_token_iter	*iter;
	t_token_iter	*iter_out;
	char			*str[3];

	token = *token_ptr_add;
	iter = iter_ptr;
	iter_out = iter_ptr;
	str[0] = ft_strdup("");
	while (token_iter_cursor(iter) \
		<= token_iter_find(token, CLOSE_DQUOTE_TOKEN))
	{
		str[2] = str[0];
		token = token_iter_cursor(iter);
		if (token_iter_cursor(iter)->location.len > 0)
		{
			if (token_iter_peek(iter) == DOLLAR_TOKEN)
				parse_dollar(&str[1], &token, read_line, iter_out);
			else
				parse_string(&str[1], &token, read_line, iter_out);
			ft_strjoin_custom(&str[0], str[2], str[1]);
		}
		else
			token_iter_next(iter);
		iter = iter_out;
	}
	iter_ptr = iter;
	*dst = str[0];
}

void	parse(char *read_line, t_token **token_ptr_add)
{
	size_t			i;
	size_t			size;
	t_token			*token;
	t_token_iter	iter;
	char			**args;
	t_token_iter	iter_ptr;

	token = *token_ptr_add;
	args = ft_calloc(1, sizeof(char *));
	size = 0;
	while (token[size].type != EOL_TOKEN)
		size++;
	iter = token_iter_value(token, size);
	iter_ptr = iter;
	i = 0;
	while (token_iter_cursor(&iter) != iter.end)
	{
		token = token_iter_cursor(&iter);
		if (token_iter_peek(&iter) != SPACE_TOKEN)
		{
			if (token_iter_peek(&iter) == DOLLAR_TOKEN)
				parse_dollar(&args[i++], &token, read_line, &iter_ptr);
			else if (token_iter_peek(&iter) == OPEN_DQUOTE_TOKEN)
				parse_dquote(&args[i++], &token, read_line, &iter_ptr);
			else
				parse_string(&args[i++], &token, read_line, &iter_ptr);
			ft_realloc_array(&args, i + 1);
		}
		else
			token_iter_next(&iter_ptr);
		iter = iter_ptr;
	}
	args[i] = NULL;
	size = 0;
	while (args[size] != 0)
	{
		printf("args[%zu]:%s\n", size, args[size]);
		size++;
	}
	printf("args[%zu]:%s\n", size, args[size]);
	free(args[0]);
	free(args);
}

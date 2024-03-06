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
#include "token_iter.h"

void	parse_string(char **dst, t_token **token, char *read_line);
void	parse_dollar(char **dst, t_token **token, char *read_line);
void	parse_dquote(char **dst, t_token **token, char *read_line);

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

/* int	expand_env(char **dst, char *read_line, t_token *token)
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
} */

/* void	parse(char *read_line, t_token **token_ptr_add)
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
} */

void	parse_string(char **dst, t_token **token_ptr_add, char *read_line)
{
	t_token	*token;

	token = *token_ptr_add;
	ft_substr_custom(dst, read_line, token->location.start, token->location.len);
}

void	parse_dquote(char **dst, t_token **token_ptr_add, char *read_line)
{
	t_token_iter	iter;
	size_t			size;
	t_token			*token;
	char			*dollar_str;
	char			*string_str;
	char			*quote_str;
	char			*tmp;

	token = *token_ptr_add;
	quote_str = ft_strdup("");
	size = 0;
	while (token[size].type != CLOSE_DQUOTE_TOKEN)
		size++;
	iter = token_iter_value(token, size);
	while (token_iter_cursor(&iter) != iter.end)
	{
		tmp = quote_str;
		if (token_iter_cursor(&iter)->location.len > 0)
		{
			if (token_iter_peek(&iter) == DOLLAR_TOKEN)
			{
				token = token_iter_cursor(&iter);
				parse_dollar(&dollar_str, &token, read_line);
				quote_str = ft_strjoin(tmp, dollar_str);
				free(dollar_str);
				free(tmp);
			}
			else
			{
				token = token_iter_cursor(&iter);
				parse_string(&string_str, &token, read_line);
				quote_str = ft_strjoin(tmp, string_str);
				free(string_str);
				free(tmp);
			}
		}
		token_iter_next(&iter);
	}
	token_iter_next(&iter);
	*dst = quote_str;
}

void	parse_dollar(char **dst, t_token **token_ptr_add, char *read_line)
{
	char	*env_str;
	char	*expand_str;
	t_token	*token;

	token = *token_ptr_add;
	ft_substr_custom(&env_str, read_line, token->location.start, token->location.len);
	expand_str = getenv(env_str);
	if (!expand_str)
		expand_str = "";
	*dst = ft_strdup(expand_str);	
	free(env_str);
}

void	parse(char *read_line, t_token **token_ptr_add)
{
	size_t			i;
	size_t			size;
	t_token			*token;
	t_token_iter	iter;
	char			**args;

	token = *token_ptr_add;
	args = ft_calloc(1, sizeof(char *));
	i = 0;
	size = 0;
	while (token[size].type != EOL_TOKEN)
		size++;
	iter = token_iter_value(token, size);
	while (token_iter_cursor(&iter) != iter.end)
	{
		if (token_iter_cursor(&iter)->location.len > 0)
		{
			if (token_iter_peek(&iter) == DOLLAR_TOKEN)
			{
				token = token_iter_cursor(&iter);
				parse_dollar(&args[i], &token, read_line);
			}
			else if (token_iter_peek(&iter) == OPEN_DQUOTE_TOKEN)
			{
				token = token_iter_cursor(&iter);
				parse_dquote(&args[i], &token, read_line);
			}
			else
			{
				token = token_iter_cursor(&iter);
				parse_string(&args[i], &token, read_line);
			}
			i++;
			ft_realloc_array(&args, i + 1);
		}	
		token_iter_next(&iter);
	}
	args[i] = NULL;
	size = 0;
	while (args[size] != 0)
	{
		printf("args[%zu]:%s\n", size, args[size]);
		size++;
	}
	printf("args[%zu]:%s\n", size, args[size]);
}
	
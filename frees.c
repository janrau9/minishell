/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 09:09:55 by jberay            #+#    #+#             */
/*   Updated: 2024/03/15 09:10:49 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freestruct(t_cmd **cmd)
{
	t_cmd	*tmp;
	size_t	i;

	tmp = *cmd;
	i = 0;
	while (tmp[i].cmd != NULL)
	{
		ft_freearr(&tmp[i].cmd);
		ft_freearr(&tmp[i].redir);
		i++;
	}
	free(tmp);
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
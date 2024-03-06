/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:22:09 by jberay            #+#    #+#             */
/*   Updated: 2024/02/02 08:23:46 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_str(char *str, t_print *sp_ap)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_print_char((int)*str, sp_ap);
		if (sp_ap->write_err == -1)
			break ;
		str++;
	}
}

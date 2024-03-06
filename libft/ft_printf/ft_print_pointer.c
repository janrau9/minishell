/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:22:45 by jberay            #+#    #+#             */
/*   Updated: 2024/02/02 08:24:16 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_pointer(unsigned long u, t_print *sp_ap)
{
	char	*sym;

	sym = "0123456789abcdef";
	if (u >= 16)
		ft_print_pointer(u / 16, sp_ap);
	ft_print_char(sym[u % 16], sp_ap);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:21:42 by jberay            #+#    #+#             */
/*   Updated: 2024/02/02 08:23:35 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_nbr(long n, int base, int hex_case, t_print *sp_ap)
{
	char	*sym;

	sym = "0123456789abcdef";
	if (hex_case == 1)
		sym = "0123456789ABCDEF";
	if (n < 0)
	{
		ft_print_char('-', sp_ap);
		if (sp_ap->write_err == -1)
			n = 0;
		n = n * -1;
	}
	if (n >= base)
		ft_print_nbr(n / base, base, hex_case, sp_ap);
	ft_print_char(sym[n % base], sp_ap);
}

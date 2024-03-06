/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:23:41 by jberay            #+#    #+#             */
/*   Updated: 2024/02/02 08:23:57 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
* %c Prints a single character.
* %s Prints a string (as defined by the common C convention).
* %p The void * pointer argument has to be printed in hexadecimal format.
* %d Prints a decimal (base 10) number.
* %i Prints an integer in base 10.
* %u Prints an unsigned decimal (base 10) number.
* %x Prints a number in hexadecimal (base 16) lowercase format.
* %X Prints a number in hexadecimal (base 16) uppercase format.
* %% Prints a percent sign.
*/

static void	ft_print_format(char conv, t_print *sp_ap)
{
	if (conv == 'c')
		ft_print_char(va_arg(sp_ap->ap, int), sp_ap);
	else if (conv == 's')
		ft_print_str(va_arg(sp_ap->ap, char *), sp_ap);
	else if (conv == 'p')
	{
		ft_print_str("0x", sp_ap);
		if (sp_ap->write_err != -1)
			ft_print_pointer((unsigned long)va_arg(sp_ap->ap, void *), sp_ap);
	}
	else if (conv == 'd' || conv == 'i')
		ft_print_nbr((long)va_arg(sp_ap->ap, int), 10, 0, sp_ap);
	else if (conv == 'u')
		ft_print_nbr((unsigned int)va_arg(sp_ap->ap, int), 10, 0, sp_ap);
	else if (conv == 'x')
		ft_print_nbr(va_arg(sp_ap->ap, unsigned int), 16, 0, sp_ap);
	else if (conv == 'X')
		ft_print_nbr(va_arg(sp_ap->ap, unsigned int), 16, 1, sp_ap);
	else if (conv == '%')
		ft_print_char('%', sp_ap);
	else
		sp_ap->write_err = -1;
}

static void	init_va(t_print *sp_ap, va_list ap)
{
	va_copy(sp_ap->ap, ap);
	sp_ap->length = 0;
	sp_ap->write_err = 0;
}

int	ft_printf(const char *src, ...)
{
	va_list	aptr;
	t_print	*sp_ap;
	t_print	s_ap;

	init_va(&s_ap, aptr);
	sp_ap = &s_ap;
	va_start (sp_ap->ap, src);
	while (*src != '\0')
	{
		if (*src == '%')
		{
			ft_print_format(*(++src), sp_ap);
			if (sp_ap->write_err == -1)
				break ;
		}
		else
		{
			ft_print_char(*src, sp_ap);
			if (sp_ap->write_err == -1)
				break ;
		}
		src++;
	}
	va_end(sp_ap->ap);
	return (sp_ap->length);
}

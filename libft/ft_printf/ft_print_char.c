/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:20:50 by jberay            #+#    #+#             */
/*   Updated: 2024/02/02 08:23:39 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_char(int c, t_print *sp_ap)
{
	int	len;

	len = 0;
	if (sp_ap->write_err != -1)
		len = write (1, &c, 1);
	if (len == -1)
		sp_ap->write_err = -1;
	sp_ap->length += len;
}

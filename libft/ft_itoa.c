/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:07:35 by jberay            #+#    #+#             */
/*   Updated: 2023/11/01 15:50:42 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit(long n, int sign);
static char	*putint(long n, int sign, char *ptr, int noz);

char	*ft_itoa(int n)
{
	long	x;
	int		i;
	char	*ptr;
	int		sign;
	int		noz;

	sign = 1;
	x = (long)n;
	if (n < 0)
	{
		x = (long)n * -1;
		sign = -1;
	}
	noz = get_digit(x, sign);
	i = 0;
	ptr = malloc((noz + 1));
	if (!ptr)
		return (0);
	return (putint(x, sign, ptr, noz));
}

static char	*putint(long n, int sign, char *ptr, int noz)
{
	int	i;

	if (sign == -1)
		ptr[0] = '-';
	i = 0;
	while (n >= 10)
	{
		ptr[noz - i -1] = '0' + n % 10;
		n = n / 10;
		i++;
	}
	ptr[noz - i -1] = '0' + n % 10;
	ptr[noz] = 0;
	return (ptr);
}

static int	get_digit(long n, int sign)
{
	int	x;

	x = 0;
	while (n >= 10)
	{
		n = n / 10;
		x++;
	}
	if (sign == 1)
		return (x +1);
	return (x +2);
}

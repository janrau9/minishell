/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 08:15:37 by jberay            #+#    #+#             */
/*   Updated: 2024/01/11 08:15:38 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check(unsigned long long n, int sign);

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	sign = 1;
	result = 0;
	if (*str == '\0')
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if ((*str >= 0) && (*str == '-' || *str == '+'))
		str++;
	while ((*str >= '0' && *str <= '9'))
	{
		result = result * 10 + (*str - '0');
		if (result > 9223372036854775807)
		{
			result = check(result, sign);
			break ;
		}
		str++;
	}
	return ((int)result * sign);
}

static int	check(unsigned long long n, int sign)
{
	if (n > 9223372036854775807 && sign == 1)
		return (-1);
	else if (n > 9223372036854775807 && sign == -1)
		return (0);
	else
		return (1);
}

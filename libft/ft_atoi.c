/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:07:53 by hyko              #+#    #+#             */
/*   Updated: 2022/12/31 17:03:16 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long
	atoi_sub(const char *str, long long i, long long sign, long long result)
{
	while ('0' <= str[i] && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if (result * sign > 2147483647)
			return (-1);
		else if (result * sign < -2147483648)
			return (-1);
		i++;
	}
	while (str[i])
	{
		if (!((9 <= str[i] && str[i] <= 13) || str[i] == 32 || str[i] == 0))
			return (-1);
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	long long	i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	result = atoi_sub(str, i, sign, result);
	if (result == -1)
		return (-1);
	return (result * sign);
}

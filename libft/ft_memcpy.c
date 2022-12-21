/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:10:08 by hyko              #+#    #+#             */
/*   Updated: 2022/01/16 20:23:48 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst == 0 && src == 0 && n > 0)
		return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (dst == 0 && src == 0 && n > 0)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

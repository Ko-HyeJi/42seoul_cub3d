/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:12:05 by hyko              #+#    #+#             */
/*   Updated: 2022/01/15 23:33:25 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cp_s1;
	unsigned char	*cp_s2;

	i = 0;
	cp_s1 = (unsigned char *)s1;
	cp_s2 = (unsigned char *)s2;
	while (i < n && cp_s1[i] != '\0')
	{
		if (cp_s1[i] != cp_s2[i])
			return (cp_s1[i] - cp_s2[i]);
		i++;
	}
	if (cp_s1[i] == '\0' && i < n)
		return (cp_s1[i] - cp_s2[i]);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:11:04 by hyko              #+#    #+#             */
/*   Updated: 2022/01/17 22:15:49 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static char	**ft_malloc_error(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	if (s[0] == '\0')
		return (0);
	i = 0;
	count = 0;
	if (s[0] != c)
		count++;
	while (s[i + 1] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		total_word;
	int		next_word_len;
	int		i;

	if (s == NULL)
		return (NULL);
	total_word = word_count(s, c);
	str = (char **)malloc(sizeof(char *) * (total_word + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i < total_word)
	{
		while (*s == c)
			s++;
		next_word_len = word_len(s, c);
		str[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		if (str[i] == NULL)
			return (ft_malloc_error(str));
		ft_strlcpy(str[i], s, next_word_len + 1);
		s += next_word_len;
	}
	str[i] = NULL;
	return (str);
}

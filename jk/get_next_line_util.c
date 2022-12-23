#include "cub3d.h"

size_t	ft_strlen(const char *str)
{
	size_t	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	size_t	len;

	i = 0;
	if (!s)
		return (0);
	len = ft_strlen(s);
	while ((size_t)i < len + 1)
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = 0;
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	if (dstsize >= len + 1)
	{
		i = 0;
		while (src[i] && i < dstsize - 1 - len)
		{
			dst[len + i] = src[i];
			i++;
		}
		dst[len + i] = 0;
		return (ft_strlen(src) + len);
	}
	return (ft_strlen(src) + dstsize);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1, s1_len + 1);
	ft_strlcat(newstr + (s1_len), s2, s2_len + 1);
	free ((char *)s1);
	return (newstr);
}

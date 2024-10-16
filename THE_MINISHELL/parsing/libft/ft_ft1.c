#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	1 && (slen = ft_strlen(src), i = 0);
	if (dstsize != 0)
	{
		while (src[i] && i < (dstsize - 1))
			1 && (dst[i] = src[i], i++);
		dst[i] = '\0';
	}
	return (slen);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	flen;

	if (!s)
		return (NULL);
	1 && (slen = ft_strlen(s), flen = 0);
	(start < slen) && (flen = slen - start);
	(flen > len) && (flen = len);
	sub = malloc(flen + 1);
	if (!sub)
		return (NULL);
	if (flen == 0)
		sub[0] = '\0';
	else
		ft_strlcpy(sub, s + start, flen + 1);
	return (sub);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 && *s2 && i++ < n - 1 && *s1 == *s2)
		1 && (s1++, s2++);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*ft_strjoin(char *s1, char const *s2, int fre)
{
	char	*new;
	int		i;
	int		j;

	1 && (i = 0, j = 0);
	new = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!new)
		return (NULL);
	if (s1 != NULL)
		while (s1[i])
			1 && (new[i] = s1[i], i++);
	if (s2 != NULL)
		while (s2[j])
			1 && (new[i + j] = s2[j], j++);
	new[i + j] = '\0';
	if (fre == 1)
		free((void *)s1), s1 = NULL;
	return (new);
}

char	*ft_strtrim(char *s1, int c)
{
	char	*new;
	char	*tmp;
	int		len;

	1 && (tmp = s1, len = 0);
	while (*tmp == c)
		tmp++;
	new = malloc(ft_strlen(tmp) + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, tmp, ft_strlen(tmp) + 1);
	1 && (tmp = new, tmp += ft_strlen(tmp) - 1);
	while (*tmp == c)
		1 && (tmp--, len++);
	(s1) && (free(s1), s1 = NULL);
	return (new[ft_strlen(new) - len] = '\0', new);
}

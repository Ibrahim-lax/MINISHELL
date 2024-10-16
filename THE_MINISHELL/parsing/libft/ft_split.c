#include "libft.h"

static int	count_word(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static int	ft_len(char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
		1 && (len++, s++);
	return (len);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
		1 && (free(split[i]), split[i] = NULL, i++);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word;
	int		i;
	int		len;

	1 && (word = count_word((char *)s, c), i = 0);
	split = (char **)malloc(sizeof(char *) * (word + 1));
	if (!split || !s)
		return (NULL);
	while (i < word)
	{
		while (*s == c)
			s++;
		len = ft_len((char *)s, c);
		split[i] = (char *)malloc(sizeof(char) * (len + 1));
		// if (!split[i])
		// 	return (free_split(split), NULL);
		1 && (ft_strlcpy(split[i], s, len + 1), s += len, i++);
	}
	return (split[i] = 0, split);
}

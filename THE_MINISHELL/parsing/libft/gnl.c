#include "libft.h"

char	*gnl(int fdread)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		tmp = malloc(2);
		if (!tmp)
			return (NULL);
		tmp[1] = 0;
		if (read(fdread, tmp, 1) > 0)
			line = ft_strjoin(line, tmp, 1);
		if (!*tmp || *tmp == '\n')
			break ;
		free(tmp);
	}
	return (free(tmp), line);
}

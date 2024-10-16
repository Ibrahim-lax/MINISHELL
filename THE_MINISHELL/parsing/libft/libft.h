#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>

int		ft_isalnum(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char *s1, int c);
char	*ft_strjoin(char *s1, char const *s2, int fre);
char	**ft_split(char const *s, char c);
char	*gnl(int fdread);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

void	ft_putstr_fd(char *s, int fd);
void	free_split(char **split);

#endif
#include "minishell.h"
#include "GNL/get_next_line.h"

char	*ftr_strjoin(char *s1, char const *s2, int fre)
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

int	exa_single_nb_cmdd(char **env, int fd0, int fd1)
{
	pid_t	pid;
	int		ret = 500;
	char	*p;
	char 	*arg[] = {"ls", " " ,"-l",  NULL};

	pid = fork();
 	// printf("HELLO BOI");fflush(stdout);
	if (pid == 0)
	{
		close(fd0);
		dup2(fd1, STDOUT_FILENO);
		p = ftr_strjoin("/bin", "/", 0);
		p = ftr_strjoin(p, "ls", 0);
		if (execve(p, arg, env) == -1)
			perror("execve error :");
	}
	else
	{
		waitpid(-1, &ret, 0);
		// dup2(STDOUT_FILENO, fd1);
		printf("RIGHT AFTER THE WAITPID : HELLO BOI\n");fflush(stdout);
		return ret;
	}
	return 0;
}

int main(int argc, char const *argv[], char **env)
{
	char	*gnl;
	char	*c = ft_strdup("");
	int		fd[2];

	if (pipe(fd) == -1)
		perror("PROBLEM IN PIPE");
	int exit_st = exa_single_nb_cmdd(env, fd[0], fd[1]);
	close(fd[1]);
	gnl = get_next_line(fd[0]);
	if (!gnl)
		return (printf("DIDNT WORK"), 1);
	while (gnl)
	{
		c = ftr_strjoin(c, gnl, 1);
		free(gnl);
		gnl = get_next_line(fd[0]);
	}
	close(fd[0]);
	printf("the stuff collected is [%s]\nexit_status is :%d\n", c, exit_st);
	return 0;
}

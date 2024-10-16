
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

int run_pwd()
{
	char	*c;

	c = malloc(PATH_MAX);
	if (!getcwd(c, PATH_MAX))
	{
		perror("pwd: error retrieving current directory: getcwd: cannot access parent directories");
		return (1);
	}
	printf("%s\n", c);
	free(c);
	return (0);
}

int run_echo(int argc, char **argv)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
    while (i < argc && argv[i][0] == '-' && argv[i][1] == 'n' && argv[i][2] == '\0')
    {
        nl = 0;
        i++;
    }
    while (i < argc)
    {
        if (i > 1)
            write(1, " ", 1);
        write(1, argv[i], strlen(argv[i]));
        i++;
    }
    if (nl)
    write(1, "\n", 1);
    return (0);
}

int main(int argc, char *argv[])
{
	int	exit_status;

	exit_status = run_echo(argc, argv);
    return exit_status;
}

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int	main(int ac, char *av[], char **env)
{
	char *arg1[] = {"cat", "-n", "outfile", NULL};
	char *arg2[] = {"cd", NULL};
	char *arg3[] = {"/bin/pwd", NULL};

	if (fork() == 0)
	{
		printf("Child:\n");
		execve("/usr/bin/cd", arg2, env);
	}
	else
	{
		printf("Parent:\n");
		execve("/bin/pwd", arg3, NULL);
	}
	return (0);
}

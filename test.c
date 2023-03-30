# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int	main(int ac, char *av[], char **env)
{
	char *arg1[] = {"cat", "-n", "file1", "outfile", NULL};
	char *arg2[] = {"cd", NULL};
	char *arg3[] = {"/bin/pwd", NULL};
	char *arg4[] = {"/bin/ls", NULL};
	char *cmd[] = {"ls", "", NULL};

	if (fork() == 0)
	{
		printf("Child:\n");
		execve("/bin/ls", cmd, env);
	}
	else
	{
		printf("Parent:\n");
		//execve("/bin/pwd", arg3, NULL);
	}
	return (0);
}

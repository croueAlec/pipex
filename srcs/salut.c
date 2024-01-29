#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char const **argv, char **envp)
{
	char	*arg_tab[3];
	char	src[50] = "/bin/";
	__pid_t	pid;
	int	fd = open("tac1.txt", O_RDONLY);
	if (argc == 1)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		printf("child process : %d\n", pid);
	else
		printf("parent process : %d\n", pid);
	if (pid == 0)
	{
		arg_tab[0] = (char *)argv[1];
		arg_tab[1] = (char *)argv[2];
		arg_tab[2] = NULL;
		execve(strcat(src, arg_tab[0]), arg_tab, envp);
	}
	sleep(2);
	if (!strcmp("touch", argv[1]) && argv[2] && unlink(argv[2]) == 0)
		printf("Successfully deleted %s\n", argv[2]);
	printf("test %d\n", pid);
	close(fd);
	return (0);
}


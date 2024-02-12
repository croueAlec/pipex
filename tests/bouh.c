#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[], char **envp)
{
	int pid1;
	int pid2;

	int pipefd[2];
	char	*str;

	str = malloc((4 + 1) * sizeof(char));
	if(!str)
		return (0);

	if (pipe(pipefd) == -1)
		return (errno);
	pid1 = fork();
	if (pid1 == 0)
	{
		if (close(pipefd[0]))
			return (errno);
		// write(pipefd[1], "bonjour", 9);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execve("/usr/bin/ls", &argv[1], envp);
		if (close(pipefd[1]))
			return (free(str), errno);
		return (0);
	}

	pid2 = fork();
	if (pid2 == 0)
	{
		char buf[4000] = {0};
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		read(pipefd[0], &buf, 4000);
		// write(0, buf, 9);
		printf("%s", buf);
		close(pipefd[0]);
		return (free(str), 0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	return (free(str), 0);
}

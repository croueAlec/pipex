#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int pid1;
	int pid2;

	int pipefd[2];

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		write(pipefd[1], "bonjour", 9);
		close(pipefd[1]);
		return 0;
	}

	pid2 = fork();
	if (pid2 == 0)
	{
		char buf[9];
		close(pipefd[1]);
		read(pipefd[0], &buf, 9);
		write(0, buf, 9);
		close(pipefd[0]);
		return 0;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return 0;
}

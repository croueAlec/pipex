#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if (argc == 1)
		return (0);
	if (access(argv[1], F_OK) == 0)
		printf("file exists\n");
	if (access(argv[1], R_OK) == 0)
		printf("file can be read\n");
	if (access(argv[1], W_OK) == 0)
		printf("file can be written into\n");
	if (access(argv[1], X_OK) == 0)
		printf("file can be executed\n");
	return (0);
}

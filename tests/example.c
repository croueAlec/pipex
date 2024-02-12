#include <stdio.h>

int main(int argc, char const *argv[])
{
	if (argc == 1)
		printf("This is a simple example\n");
	else
		printf("This is an example\t %s\n", argv[1]);
	return 0;
}

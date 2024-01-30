#include <stdio.h>

int main(int ac, char **av)
{
	printf("%s\n", av[0]);
	return (0);
}
// executer ca depuis Documents


/* ac48v ~:  < pouetpouet cat | cat /dev/rando >
ac48v ~:  touch out
ac48v ~:  chmod 000 out 
ac48v ~:  < pouetpouet cat | cat /dev/random > out
zsh: no such file or directory: pouetpouet
zsh: permission denied: out
 */

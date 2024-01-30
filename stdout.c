#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "libs/libft/libft.h"

char	*find_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] && strncmp("PATH", env[i], 4))
		i++;
	if (!env[i])
		return (NULL);
	printf("%s\n\n", &env[i][5]);
	return (&env[i][5]);
}

int	check_path_env(char *path, char *command)
{
	char	*tmp;
	tmp = ft_strdup(path);
	tmp = ft_sep_join(tmp, command, "/");
	if (!tmp || access(tmp, X_OK))
		return (free(tmp), 0);
	return (free(tmp), 1);
}

char	*find_cmd(char **envp, char **argv)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	envp = ft_split(find_path(envp), ':');
	while (envp && envp[i])
	{
		if (check_path_env(envp[i], argv[1]) && tmp == NULL)
			tmp = ft_strdup(envp[i]);
		free(envp[i]);
		i++;
	}
	return (free(envp), tmp);
}

int	execute_cmd(char *path, char **cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	printf("%d\n", pid);
	if (pid == 0)
		execve(ft_sep_join(path, cmd[0], "/"), cmd, envp);
	return (0);
}

int	is_directory(char *str)
{
	if (str[0] == '/' && ft_isascii(str[1]))
		return (1);
	if (str[0] == '.' && str[1] == '/' && ft_isascii(str[2]))
		return (1);
	if (!ft_memcmp("../", str, 3) && ft_isascii(str[3]))
		return (1);
	return (0);
}

void	check_input(char **argv, char **envp)
{
	if (is_directory(argv[1]))
		printf("ca / ca ./ ou ca ../\n");
	else if (ft_strchr(argv[1], '/'))
		printf("contient un /\n");
	else
		printf("juste une commande\n");
}

int main(int argc, char *argv[], char **envp)
{
	char	*path;

	if (!envp[0])
		return (printf("No env\n"));
	if (argc == 1)
		return (printf("No arg\n"));
	check_input(argv, envp);
	// if (access(argv[1], X_OK) == 0)
	// 	return (0);
	path = find_cmd(envp, argv);
	printf("%s\n", path);
	execute_cmd(path, &argv[1], envp);
	wait(NULL);
	return (free(path), 0);
}

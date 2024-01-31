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
		if (check_path_env(envp[i], argv[0]) && tmp == NULL)
			tmp = ft_strdup(envp[i]);
		free(envp[i]);
		i++;
	}
	return (free(envp), ft_sep_join(tmp, argv[0], "/"));
}

int	execute_cmd(char *path, char **cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	printf("%d\n", pid);
	if (pid == 0)
		execve(path, cmd, envp);
	return (0);
}

int	is_directory(char *str)
{
	if (!ft_memcmp("/", str, 1))
		return (1);
	if (!ft_memcmp("./", str, 2))
		return (1);
	if (!ft_memcmp("../", str, 3))
		return (1);
	return (0);
}

char	*check_input(char **argv, char **envp)
{
	if (is_directory(argv[0]))
		return (ft_strdup(argv[0]));
	else if (ft_strchr(argv[0], '/'))
		return (ft_strjoin("./", argv[0]));
	else
		return (find_cmd(envp, argv));
}

void	tab_print(char **tab)
{
	for (size_t i = 0; tab[i]; i++)
	{
		printf("[%s] ", tab[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[], char **envp)
{
	char	*path;
	char	**tmp_arg;

	if (!envp[0])
		return (printf("No env\n"));
	if (argc == 1)
		return (printf("No arg\n"));
	tmp_arg = ft_split(argv[2], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path)
		return (ft_free(tmp_arg, ft_count_words(argv[2], 32)), 0);
	// if (access(argv[1], X_OK) == 0)
	// 	return (0);
	printf("%s\n", path);
	tab_print(tmp_arg);
	execute_cmd(path, tmp_arg, envp);
	wait(NULL);
	return (free(path), 0);
}

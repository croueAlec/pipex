/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_pipex_main.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:07:18 by acroue            #+#    #+#             */
/*   Updated: 2024/02/08 16:06:25 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "libs/libft/libft.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>


char	*find_path(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] && strncmp("PATH", env[i], 4))
		i++;
	if (!env[i])
		return (NULL);
	// printf("%s\n\n", &env[i][5]);
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

int	first_fork(char **argv, char **envp, int pipefd[2])
{
	char	**tmp_arg;
	char	*path;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path)
		return (ft_free(tmp_arg, ft_count_words(argv[0], 32)), 0);
	if (close(pipefd[0]))
		return (errno);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve(path, tmp_arg, envp);
	if (close(pipefd[1]))
		return (errno);
	return (0);
}

int	normal_fork(char **argv, char **envp, int pipefd[2], int fd)
{
	char	**tmp_arg;
	char	*path;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path)
		return (ft_free(tmp_arg, ft_count_words(argv[0], 32)), 0);
	dup2(fd, STDIN_FILENO);
	if (close(pipefd[0]))
		return (errno);
	dup2(pipefd[1], STDOUT_FILENO);
	execve(path, tmp_arg, envp);
	if (close(pipefd[1]))
		return (errno);
	return (0);
}

int	last_fork(char **argv, char **envp, int pipefd[2], int fd_tmp)
{
	char	**tmp_arg;
	char	*path;
	int		fd;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path)
		return (ft_free(tmp_arg, ft_count_words(argv[0], 32)), 0);
	if (close(pipefd[1]))
		return (errno);
	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	printf("%d %d\t%d %d %s\n", pipefd[0], pipefd[1], fd_tmp, fd, argv[1]);
	dup2(fd_tmp, STDIN_FILENO);
	close(fd_tmp);
	close(pipefd[0]);
	if (fd < 0)
		return ((void)close(fd), -1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve(path, tmp_arg, envp);
	return (0);
}

int	*open_file(char **argv, int pipefd[2])
{
	int	fd;

	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
		return ((void)close(pipefd[0]), (void)close(pipefd[1]), NULL);
	if (dup2(fd, STDIN_FILENO) == -1)
		return ((void)close(pipefd[0]), (void)close(pipefd[1]), NULL);
	close(fd);
	return (pipefd);
}

static int	wait_children(int pid)
{
	int	wait_status;
	int	error_status;

	while (errno != ECHILD)
		if (wait(&wait_status) == pid && WIFEXITED(wait_status))
			error_status = WEXITSTATUS(wait_status);
	if (pid == -1)
		return (127);
	return (error_status);
}

int main(int argc, char *argv[], char **envp)
{
	pid_t	pid_one;
	int		pipefd[2];
	int		i;
	int		fd;

	i = 1;
	if (!envp[0])
		return (printf("No env\n"));
	if (argc < 5)
		return (printf("Not enough args\n"));
	while (++i < argc - 1)
	{
		if (pipe(pipefd) == -1)
			return (errno);
		pid_one = fork();
		if (pid_one)
		{
			close(pipefd[1]);
			close(fd);
			fd = pipefd[0];
		}
		if (i == 2 && pid_one == 0)
		{
			first_fork(&argv[i], envp, open_file(&argv[1], pipefd));
		}
		if (i == argc - 2 && pid_one == 0)
		{
			last_fork(&argv[i], envp, pipefd, fd);
		}
		else if (pid_one == 0)
			normal_fork(&argv[i], envp, pipefd, fd);
	}
	close(fd);
	wait_children(pid_one);
	return (0);
}

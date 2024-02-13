/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:49:34 by acroue            #+#    #+#             */
/*   Updated: 2024/02/13 16:31:16 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_fork(char **tmp_arg, char **argv, char *path, int status)
{
	free(path);
	ft_free(tmp_arg, ft_count_words(argv[0], 32));
	exit(status);
	return (0);
}

int	first_fork(char **av, char **envp, int pipfd[2], int infile)
{
	char	**arg;
	char	*path;

	arg = ft_split(av[0], 32);
	path = check_input(arg, envp);
	if (!arg || !path || infile < 0)
		return (free_pipex(0, pipfd[0], pipfd[1]), free_fork(arg, av, path, 0));
	close(pipfd[0]);
	if (dup2(infile, STDIN_FILENO) < 0)
		return (free_pipex(0, infile, pipfd[1]), free_fork(arg, av, path, 0));
	close(infile);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		return (free_pipex(0, -1, pipfd[1]), free_fork(arg, av, path, 0));
	close(pipfd[1]);
	if (execve(path, arg, envp) == -1)
		ft_dprintf(STDERR_FILENO, "%s : command not found\n", av[0]);
	return (free_fork(arg, av ,path, 127));
}

int	middle_fork(char **av, char **envp, int pipfd[2], int fd)
{
	char	**arg;
	char	*path;

	arg = ft_split(av[0], 32);
	path = check_input(arg, envp);
	if (!arg || !path || fd < 0)
		return (free_pipex(0, pipfd[0], pipfd[1]), free_fork(arg, av, path, 0));
	if (dup2(fd, STDIN_FILENO))
		return (free_pipex(0, pipfd[0], pipfd[1]), free_fork(arg, av, path, 0));
	close(fd);
	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		return (free_pipex(0, -1, pipfd[1]), free_fork(arg, av, path, 0));
	close(pipfd[1]);
	if (execve(path, arg, envp) == -1)
		ft_dprintf(STDERR_FILENO, "%s : command not found\n", av[0]);
	return (free_fork(arg, av, path, 127));
}

int	last_fork(char **av, char **envp, int pipfd[2], int bonus)
{
	char	**arg;
	char	*path;
	int		fd;

	arg = ft_split(av[0], 32);
	path = check_input(arg, envp);
	if (!arg || !path)
		return (free_pipex(0, pipfd[0], pipfd[1]), free_fork(arg, av, path, 0));
	close(pipfd[1]);
	if (bonus)
		fd = open(av[1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(av[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror("Outfile"), close(pipfd[0]),free_fork(arg, av, path, 1));
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		return (free_pipex(0, pipfd[0], fd), free_fork(arg, av, path, 0));
	close(pipfd[0]);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (free_pipex(0, -1, fd), free_fork(arg, av, path, 0));
	close(fd);
	if (execve(path, arg, envp) == -1)
		ft_dprintf(STDERR_FILENO, "%s : command not found\n", av[0]);
	return (free_fork(arg, av, path, 127));
}

void	manage_children(int pipefd[2], t_args args, size_t argc, int tmp_fd)
{
	if (args.i == 2 || (args.bonus == 1 && args.i == 3))
		first_fork(&args.argv[args.i], args.envp, pipefd, tmp_fd);
	else if (args.i == argc - 2)
		last_fork(&args.argv[args.i], args.envp, pipefd, args.bonus);
	else if (args.i > 2 && args.i < argc + 2)
		middle_fork(&args.argv[args.i], args.envp, pipefd, tmp_fd);
	ft_printf("NOT SUPPOSED TO HAPPEN\n");
}

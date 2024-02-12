/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:49:34 by acroue            #+#    #+#             */
/*   Updated: 2024/02/12 19:00:59 by acroue           ###   ########.fr       */
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

int	first_fork(char **argv, char **envp, int pipefd[2], int infile)
{
	char	**tmp_arg;
	char	*path;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path || infile < 0)
		return (free_fork(tmp_arg, argv, path, 0));
	close(pipefd[0]);
	if (dup2(infile, STDIN_FILENO) < 0)
		free_fork(tmp_arg, argv, path, errno);
	close(infile);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		free_fork(tmp_arg, argv, path, errno);
	close(pipefd[1]);
	if (execve(path, tmp_arg, envp) == -1)
		ft_dprintf(STDERR_FILENO, "%s : command not found", argv[0]);
	return (free_fork(tmp_arg, argv ,path, 127));
}

int	middle_fork(char **argv, char **envp, int pipefd[2], int fd)
{
	char	**tmp_arg;
	char	*path;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path || fd < 0)
		return (free_fork(tmp_arg, argv, path, 1));
	if (dup2(fd, STDIN_FILENO))
		free_fork(tmp_arg, argv, path, errno);
	close(fd);
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		free_fork(tmp_arg, argv, path, errno);
	close(pipefd[1]);
	if (execve(path, tmp_arg, envp) == -1)
		ft_dprintf(STDERR_FILENO, "%s : command not found", argv[0]);
	return (free_fork(tmp_arg, argv, path, 127));
}

int	last_fork(char **argv, char **envp, int pipefd[2], int bonus)
{
	char	**tmp_arg;
	char	*path;
	int		fd;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path)
		return (free_fork(tmp_arg, argv, path, 1));
	if (!close(pipefd[1]))
		return (errno);
	if (bonus)
		fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		(perror("Outfile"), free_fork(tmp_arg, argv, path, 1));
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		free_fork(tmp_arg, argv, path, errno);
	close(pipefd[0]);
	if (dup2(fd, STDOUT_FILENO) < 0)
		free_fork(tmp_arg, argv, path, errno);
	close(fd);
	if (execve(path, tmp_arg, envp) == -1)
		ft_dprintf(STDERR_FILENO, "%s : command not found", argv[0]);
	return (free_fork(tmp_arg, argv, path, 127));
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

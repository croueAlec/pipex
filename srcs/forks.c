/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:49:34 by acroue            #+#    #+#             */
/*   Updated: 2024/02/09 19:46:10 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_fork(char **argv, char **envp, int pipefd[2], int infile)
{
	char	**tmp_arg;
	char	*path;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path)
		return (ft_free(tmp_arg, ft_count_words(argv[0], 32)), 0);
	if (close(pipefd[0]))
		return (errno);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execve(path, tmp_arg, envp);
	if (close(pipefd[1]))
		return (errno);
	return (0);
}

int	middle_fork(char **argv, char **envp, int pipefd[2], int fd)
{
	char	**tmp_arg;
	char	*path;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path)
		return (ft_free(tmp_arg, ft_count_words(argv[0], 32)), 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (execve(path, tmp_arg, envp) == -1)
		write(2, "Fail command\n", 14);
	return (0);
}

int	last_fork(char **argv, char **envp, int pipefd[2])
{
	char	**tmp_arg;
	char	*path;
	int		fd;

	tmp_arg = ft_split(argv[0], 32);
	path = check_input(tmp_arg, envp);
	if (!tmp_arg || !path)
		return (ft_free(tmp_arg, ft_count_words(argv[0], 32)), 0);
	if (!close(pipefd[1]))
		return (errno);
	fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[0]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (execve(path, tmp_arg, envp) == -1)
		write(2, "Fail command\n", 14);
	return (0);
}

void	manage_children(int pipefd[2], t_args args, size_t argc, int tmp_fd)
{
	if (args.i == 2)
		first_fork(&args.argv[2], args.envp, pipefd, tmp_fd);
	if (args.i == argc - 2)
		last_fork(&args.argv[args.i], args.envp, pipefd);
	else if (args.i > 2 && args.i < argc + 2)
		middle_fork(&args.argv[args.i], args.envp, pipefd, tmp_fd);
	ft_printf("NOT SUPPOSED TO HAPPEN\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:20:32 by acroue            #+#    #+#             */
/*   Updated: 2024/02/08 19:53:04 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_args(t_args *args, char **argv, char **envp)
{
	args->i = 1;
	args->argv = argv;
	args->envp = envp;
}

int	open_file(char **argv)
{
	int	fd;

	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
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

int	main(int argc, char *argv[], char **envp)
{
	t_args	args;
	pid_t	pid;
	int		pipefd[2];
	int		fd;

	init_args(&args, argv, envp);
	fd = open_file(&args.argv[1]);
	while (++args.i < (size_t)argc - 1)
	{
		if (args.i < (size_t)argc - 2)
		{
			pipe(pipefd);
		}
		pid = fork();
		if (pid == 0)
			manage_children(pipefd, args, (size_t)argc, fd);
		else
		{
			close(pipefd[1]);
			close(fd);
			fd = pipefd[0];
		}
	}
	wait_children(pid);
	return (0);
}

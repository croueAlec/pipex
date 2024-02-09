/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:20:32 by acroue            #+#    #+#             */
/*   Updated: 2024/02/09 19:42:57 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_args(t_args *args, char **argv, char **envp, int argc)
{
	args->i = 1;
	if (ft_memcmp(argv[0], "./pipex_bonus", 14) == 0)
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
			args->i = 2;
	args->argv = argv;
	args->envp = envp;
	args->argc = argc;
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

int	arg_error(int is_bonus)
{
	ft_putstr_fd(E_ARG, 2);
	if (!is_bonus)
		return (ft_putstr_fd(E_ARG_NBR, 2), -1);
	ft_putstr_fd(E_ARG_BONUS, 2);
	return (ft_putstr_fd(E_ARG_HDOC, 2), -1);
}

int	main(int argc, char *argv[], char **envp)
{
	t_args	args;
	pid_t	pid;
	int		pipefd[2];
	int		fd;

	if ((ft_memcmp(argv[0], "./pipex_bonus", 14) != 0 && argc != 5) || argc < 5)
		return (arg_error(ft_memcmp(argv[0], "./pipex_bonus", 14) == 0));
	init_args(&args, argv, envp, argc);
	fd = open_file(&args, ft_memcmp(argv[0], "./pipex_bonus", 14) == 0);
	while (++args.i < (size_t)argc - 1)
	{
		if (args.i < (size_t)argc - 2)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
			manage_children(pipefd, args, (size_t)argc, fd);
		else
		{
			(close(pipefd[1]), close(fd));
			fd = pipefd[0];
		}
	}
	wait_children(pid);
	return (0);
}

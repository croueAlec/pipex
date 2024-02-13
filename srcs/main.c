/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:20:32 by acroue            #+#    #+#             */
/*   Updated: 2024/02/13 16:49:33 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_args(t_args *args, char **argv, char **envp, int argc)
{
	args->i = 1;
	if (ft_memcmp(&argv[0][args->offset], EX, EX_LEN) == 0)
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
	exit(error_status);
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

int	check_bonus(int ac, char **av, t_args *args)
{
	char	*str;

	args->bonus = 0;
	args->offset = ft_strlen(av[0]) - EX_LEN + 1;
	str = ft_strdup(&av[0][args->offset]);
	if (!str || ac < 5)
		return (free(str), 1);
	if (ft_memcmp(str, EX, EX_LEN) == 0 && ac > 5)
	{
		args->bonus = 1;
		return (free(str), 0);
	}
	else if (ac != 5)
		return (free(str), 1);
	return (free(str), 0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_args	args;
	pid_t	pid;
	int		pipefd[2];
	int		fd;

	if (check_bonus(argc, argv, &args))
		return (arg_error(args.bonus));
	init_args(&args, argv, envp, argc);
	fd = open_file(&args, args.bonus);
	while (++args.i < (size_t)argc - 1)
	{
		if (args.i < (size_t)argc - 2)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
			manage_children(pipefd, args, (size_t)argc, fd);
		else
		{
			if (pid < 0 && (close(pipefd[0]) || close(pipefd[0]) < 0))
				break ;
			(close(pipefd[1]), close(fd));
			fd = pipefd[0];
		}
	}
	return (wait_children(pid));
}

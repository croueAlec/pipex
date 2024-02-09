/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:20:32 by acroue            #+#    #+#             */
/*   Updated: 2024/02/09 18:08:45 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_args(t_args *args, char **argv, char **envp)
{
	args->i = 1;
	args->argv = argv;
	args->envp = envp;
}

int	open_file(char **argv, int is_bonus)
{
	int		fd;
	char	*tmp;

	if (is_bonus && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		tmp = ft_strdup(argv[1]);
		while (access(tmp, F_OK) == 0)
		{
			tmp = ft_strjoin(tmp, "a");
			printf("%s\n", tmp);
		}
		fd = open(tmp, O_RDWR | O_CREAT);
		unlink(tmp);
		free(tmp);
		return (fd);
	}
	fd = open(argv[1], O_RDONLY);
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
	init_args(&args, argv, envp);
	fd = open_file(&args.argv[0], ft_memcmp(argv[0], "./pipex_bonus", 14) == 0);
	while (++args.i < (size_t)argc - 1)
	{
		if (args.i < (size_t)argc - 2)
			pipe(pipefd);
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

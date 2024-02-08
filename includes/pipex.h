/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:32:52 by acroue            #+#    #+#             */
/*   Updated: 2024/02/08 19:52:42 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libs/libft/libft.h"
# include <errno.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_args
{
	char	**argv;
	char	**envp;
	size_t	i;
}	t_args;

//		exec.c
char	*check_input(char **argv, char **envp);

//		forks.c
int		first_fork(char **argv, char **envp, int pipefd[2], int infile);
int		middle_fork(char **argv, char **envp, int pipefd[2], int fd);
int		last_fork(char **argv, char **envp, int pipefd[2], int tmp_fd);
void	manage_children(int pipefd[2], t_args args, size_t argc, int tmp_fd);

#endif

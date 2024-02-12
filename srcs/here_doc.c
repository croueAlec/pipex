/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:43:01 by acroue            #+#    #+#             */
/*   Updated: 2024/02/12 12:12:08 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	put_here_doc(int fd, t_args *args)
{
	char	*gnl;

	if (fd < 0)
		exit(3);
	args->argv[2] = ft_strjoin(args->argv[2], "\n");
	gnl = get_next_line(0);
	while (gnl && ft_strncmp(gnl, args->argv[2], ft_strlen(args->argv[2])))
	{
		ft_putstr_fd(gnl, fd);
		free(gnl);
		gnl = get_next_line(0);
	}
	free(gnl);
	return (fd);
}

int	open_file(t_args *args, int is_bonus)
{
	int		fd;
	char	*tmp;
	char	**argv;

	argv = args->argv;
	if (is_bonus && ft_strncmp(argv[1], "here_doc", 9) == 0 && args->argc > 5)
	{
		tmp = ft_strdup(argv[1]);
		while (tmp && access(tmp, F_OK) == 0 && errno != ENOENT)
		{
			tmp = ft_strnjoin(tmp, "_doc", 4);
		}
		if (!tmp)
			fd = -1;
		else
			fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return ((void)unlink(tmp), free(tmp), put_here_doc(fd, args));
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Infile");
		exit(3);
	}
	return (fd);
}

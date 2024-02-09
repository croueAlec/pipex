/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 19:43:01 by acroue            #+#    #+#             */
/*   Updated: 2024/02/09 20:06:58 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	put_here_doc(int fd, t_args *args)
{
	char	*gnl;

	if (fd < 0)
		exit(3);
	args->argv[2] = ft_strjoin(args->argv[2], "\n");
	gnl = get_next_line(fd);
	while (gnl && ft_strncmp(gnl, args->argv[2], ft_strlen(args->argv[2] + 1)))
	{
		/* continuer ici */
	}
	
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
		while (access(tmp, F_OK) == 0 && errno != ENOENT)
		{
			tmp = ft_strnjoin(tmp, "_doc", 4);
			printf("%s\n", tmp);
		}
		fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		unlink(tmp);
		free(tmp);
		return (put_here_doc(fd, args));
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Infile");
		exit(3);
	}
	return (fd);
}

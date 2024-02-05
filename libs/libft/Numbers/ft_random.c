/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:47:30 by acroue            #+#    #+#             */
/*   Updated: 2024/01/24 18:48:39 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_rand(void)
{
	int		fd;
	char	buf[1];

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0 || read(fd, buf, 1) < 0)
		return ((void)close(fd), -1);
	close(fd);
	return (buf[0]);
}

int	ft_range_rand(int max)
{
	int	r;

	r = ft_rand() % max;
	if (r < 0)
		r = -r;
	return (r);
}

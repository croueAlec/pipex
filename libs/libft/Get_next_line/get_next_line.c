/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:44:01 by acroue            #+#    #+#             */
/*   Updated: 2023/12/08 13:29:17 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_newline(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == '\n')
			return (i + 1);
	return (0);
}

static int	read_buffer(int fd, char *buffer)
{
	if (buffer[0] != '\0')
	{
		return (1);
	}
	if (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		return (1);
	}
	return (0);
}

void	*ft_gnl_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src)
		return (NULL);
	while (++i < BUFFER_SIZE)
	{
		if (n && i < BUFFER_SIZE - n)
		{
			((char *)dest)[i] = ((char *)src)[i];
		}
		else
			((char *)dest)[i] = '\0';
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*tmp;
	int			nl;

	tmp = NULL;
	while ((!is_newline(tmp)) && read_buffer(fd, (char *)buffer) > 0)
	{
		nl = is_newline(buffer);
		tmp = ft_strnjoin(tmp, buffer, nl);
		if (!tmp)
			return (NULL);
		ft_gnl_memmove(buffer, &buffer[nl], nl);
	}
	return (tmp);
}

char	*super_gnl(int fd)
{
	static char	buffer[MAX_FD][BUFFER_SIZE];
	char		*tmp;
	int			nl;

	if (fd < 0 || fd > MAX_FD)
		return (NULL);
	tmp = NULL;
	while ((!is_newline(tmp)) && read_buffer(fd, (char *)buffer[fd]) > 0)
	{
		nl = is_newline(buffer[fd]);
		tmp = ft_strnjoin(tmp, buffer[fd], nl);
		if (!tmp)
			return (NULL);
		ft_gnl_memmove(buffer[fd], &buffer[fd][nl], nl);
	}
	return (tmp);
}

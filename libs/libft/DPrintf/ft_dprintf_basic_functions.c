/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_basic_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:40:14 by acroue            #+#    #+#             */
/*   Updated: 2024/02/12 18:33:05 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_dprintf.h"

int	fd_putchar(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	fd_putstr(char *s, int fd)
{
	if (!s)
	{
		return (write(fd, "(null)", 6));
	}
	else
		return (write(fd, s, ft_strlen(s)));
}

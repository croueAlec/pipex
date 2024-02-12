/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:14:53 by acroue            #+#    #+#             */
/*   Updated: 2024/02/12 18:33:26 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_dprintf.h"

static int	fd_isflag(char c)
{
	if (c == 'c' || c == 's' || c == '%')
		return (1);
	else if (c == 'd' || c == 'i' || c == 'u')
		return (1);
	else if (c == 'x' || c == 'X' || c == 'p')
		return (1);
	else
		return (0);
}

static int	fd_flag_manage(char c, va_list arg, int fd)
{
	if (c == '%')
		return (fd_putchar(37, fd));
	else if (c == 'c')
		return (fd_putchar(va_arg(arg, int), fd));
	else if (c == 's')
		return (fd_putstr(va_arg(arg, char *), fd));
	else if (c == 'd' || c == 'i')
		return (fd_put_signed(va_arg(arg, int), fd));
	else if (c == 'u')
		return (fd_put_unsigned(va_arg(arg, unsigned int), fd));
	else if (c == 'x' || c == 'X')
		return (fd_hex_zero(va_arg(arg, unsigned int), c, fd));
	else if (c == 'p')
		return (fd_hex_min(va_arg(arg, unsigned long), fd));
	else
		return (write(fd, "you are not supposed to see this", 32));
}

size_t	ft_dprintf(int fd, const char *format, ...)
{
	size_t	i;
	size_t	length;
	va_list	arg;

	i = 0;
	length = 0;
	va_start(arg, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && fd_isflag(format[i + 1]))
		{
			i++;
			length += fd_flag_manage(format[i], arg, fd);
		}
		else
		{
			fd_putchar(format[i], fd);
			length++;
		}
		i++;
	}
	va_end(arg);
	return (length);
}

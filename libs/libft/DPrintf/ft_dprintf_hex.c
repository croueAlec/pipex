/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:52:38 by acroue            #+#    #+#             */
/*   Updated: 2024/02/12 18:27:47 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_dprintf.h"

int	fd_hex_min(long long arg, int fd)
{
	if (!arg)
		return (write(fd, "(nil)", 5));
	else
		return (fd_putnbr_base(arg, "0123456789abcdef", 2, fd));
}

int	fd_hex_zero(long long arg, char c, int fd)
{
	if (arg == 0)
		return (write(fd, "0", 1));
	else if (c == 'x')
		return (fd_putnbr_base(arg, "0123456789abcdef", 0, fd));
	else if (c == 'X')
	{
		return (fd_putnbr_base(arg, "0123456789ABCDEF", 0, fd));
	}
	else
	{
		return (-1);
	}
}

int	fd_put_hex(char *str, int len, int is_address, int fd)
{
	size_t	length;

	length = 0;
	if (is_address == 2)
		length += write(fd, "0x", 2);
	else if (is_address == 1)
		length += write(fd, "-", 1);
	while (len--)
		length += write(fd, &str[len], 1);
	free(str);
	return (length);
}

int	fd_putnbr_base(unsigned long long n, char *base, int is_adr, int fd)
{
	int		b_length;
	size_t	i;
	char	*str;

	b_length = ft_strlen(base);
	i = 0;
	str = malloc((b_length + 1) * sizeof(char));
	if (!str)
		return (0);
	while (n > 0)
	{
		str[i] = base[n % b_length];
		n /= b_length;
		i++;
	}
	str[i] = '\0';
	return (fd_put_hex(str, i, is_adr, fd));
}

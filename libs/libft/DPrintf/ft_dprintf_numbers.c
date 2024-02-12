/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_numbers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:28:00 by acroue            #+#    #+#             */
/*   Updated: 2024/02/12 18:27:45 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_dprintf.h"

void	fd_print_nbr(long n, int fd)
{
	char	c;

	c = n % 10 + 48;
	if (n >= 10)
	{
		fd_print_nbr(n / 10, fd);
	}
	write(fd, &c, 1);
}

int	fd_put_signed(int n, int fd)
{
	int	length;
	int	temp;

	temp = 0;
	length = 1;
	write(fd, "-", n < 0);
	if (n == -2147483648)
		return (write(fd, "2147483648", 10) + 1);
	else if (n < 0)
	{
		length++;
		n *= -1;
	}
	temp = n;
	while (temp >= 10)
	{
		temp /= 10;
		length++;
	}
	fd_print_nbr(n, fd);
	return (length);
}

int	fd_put_unsigned(unsigned int n, int fd)
{
	unsigned int	temp;
	size_t			length;

	temp = n;
	length = 1;
	while (temp >= 10)
	{
		temp /= 10;
		length++;
	}
	fd_print_nbr(n, fd);
	return (length);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:28:00 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 17:10:57 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_nbr(long n)
{
	char	c;

	c = n % 10 + 48;
	if (n >= 10)
	{
		ft_print_nbr(n / 10);
	}
	write(1, &c, 1);
}

int	ft_put_signed(int n)
{
	int	length;
	int	temp;

	temp = 0;
	length = 1;
	write(1, "-", n < 0);
	if (n == -2147483648)
		return (write(1, "2147483648", 10) + 1);
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
	ft_print_nbr(n);
	return (length);
}

int	ft_put_unsigned(unsigned int n)
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
	ft_print_nbr(n);
	return (length);
}

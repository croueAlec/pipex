/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:52:38 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 17:11:06 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_hex_min(long long arg)
{
	if (!arg)
		return (write(1, "(nil)", 5));
	else
		return (ft_putnbr_base(arg, "0123456789abcdef", 2));
}

int	ft_hex_zero(long long arg, char c)
{
	if (arg == 0)
		return (write(1, "0", 1));
	else if (c == 'x')
		return (ft_putnbr_base(arg, "0123456789abcdef", 0));
	else if (c == 'X')
	{
		return (ft_putnbr_base(arg, "0123456789ABCDEF", 0));
	}
	else
	{
		return (-1);
	}
}

int	ft_put_hex(char *str, int len, int is_address)
{
	size_t	length;

	length = 0;
	if (is_address == 2)
		length += write(1, "0x", 2);
	else if (is_address == 1)
		length += write(1, "-", 1);
	while (len--)
		length += write(1, &str[len], 1);
	free(str);
	return (length);
}

int	ft_putnbr_base(unsigned long long n, char *base, int is_address)
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
	return (ft_put_hex(str, i, is_address));
}

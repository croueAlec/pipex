/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:33:35 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:49 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_int_len(long n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*result;
	int		sign;
	long	nnn;

	sign = 0;
	nnn = (long)n;
	if (nnn < 0)
	{
		sign = 1;
		nnn *= -1;
	}
	len = ft_int_len(nnn);
	result = ft_calloc((sign + len + 1), sizeof(char));
	if (!result)
		return (NULL);
	if (sign)
		result[0] = '-';
	while (len > 0)
	{
		result[len + sign - 1] = nnn % 10 + 48;
		nnn /= 10;
		len--;
	}
	return (result);
}

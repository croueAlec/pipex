/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:45:12 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:48 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	char			*str;
	unsigned char	character;

	character = (unsigned char)c;
	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = character;
		i++;
	}
	return (s);
}

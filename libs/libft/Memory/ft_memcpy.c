/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:12:46 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:48 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*str;
	char	*str2;

	str = (char *)dest;
	str2 = (char *)src;
	if (!str && !str2)
		return (NULL);
	i = 0;
	while (i < n)
	{
		str[i] = str2[i];
		i++;
	}
	return (dest);
}

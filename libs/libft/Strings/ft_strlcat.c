/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:46:23 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:51 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if ((!src && size == 0) || (!dst && size == 0))
		return (0);
	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (size == 0 || i > size)
		return (size + j);
	j = 0;
	while (src[j] && i + j < size - 1)
	{
		dst[j + i] = src[j];
		j++;
	}
	dst[j + i] = '\0';
	return (i + ft_strlen(src));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:20:58 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:53 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s01;
	unsigned char	*s02;

	s01 = (unsigned char *)s1;
	s02 = (unsigned char *)s2;
	i = 0;
	while ((s01[i] != '\0' || s02[i] != '\0') && i < n)
	{
		if (s01[i] != s02[i])
			return ((s01[i] - s02[i]));
		i++;
	}
	return (0);
}

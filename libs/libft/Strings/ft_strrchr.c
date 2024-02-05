/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:14:49 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:54 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		result;
	char	c2;

	c2 = (char)c;
	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c2)
		{
			result = i;
		}
		i++;
	}
	if (c2 == 0)
		return ((char *)&str[i]);
	else if (str[result] != c2)
		return (NULL);
	return ((char *)&str[result]);
}

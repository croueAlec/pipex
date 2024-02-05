/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:47:19 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:50 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	c2;

	c2 = (char)c;
	i = 0;
	while (str[i] != c2 && str[i] != '\0')
		i++;
	if (str[i] != c2)
		return (NULL);
	return ((char *)&str[i]);
}

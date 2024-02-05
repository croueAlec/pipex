/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:03:41 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:50 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*dest;
	char	*str;

	str = (char *)s;
	i = 0;
	len = ft_strlen(str);
	dest = malloc ((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

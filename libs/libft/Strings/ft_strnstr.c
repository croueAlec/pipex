/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:27:48 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:53 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		else
			i++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	size_little;
	char	*str;

	size_little = ft_strlen(little);
	str = (char *)big;
	i = 0;
	if ((!big || !little) && len == 0)
		return (NULL);
	if (size_little == 0)
		return (&str[0]);
	if (!*big && len == 0)
		return (0);
	while (big[i] != '\0' && i <= (len - size_little))
	{
		if (ft_strcmp(&big[i], little) && len != 0)
			return (&str[i]);
		else if (len == 0)
			return (NULL);
		i++;
	}
	return (NULL);
}

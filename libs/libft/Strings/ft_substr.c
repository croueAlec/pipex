/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:15:05 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:55 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_iron(void)
{
	char	*str;

	str = malloc(sizeof(char));
	str[0] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	int		size;

	if (!s)
		return (NULL);
	size = ft_strlen(s) - start;
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_iron());
	if ((size_t)size < len)
		len = size;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i + start] != '\0' && i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = 0;
	return (str);
}

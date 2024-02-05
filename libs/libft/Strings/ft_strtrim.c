/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:01:41 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 13:59:54 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_charset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (ft_charset(s1[start], set) && s1[start] != '\0')
		start++;
	while (ft_charset(s1[end - 1], set) && end > start)
		end--;
	str = malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, &s1[start], end - start);
	str[end - start] = '\0';
	return (str);
}

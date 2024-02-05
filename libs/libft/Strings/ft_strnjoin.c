/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:57:28 by acroue            #+#    #+#             */
/*   Updated: 2023/12/07 14:57:51 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_safe_strlen(s1);
	if (n)
		len2 = n;
	else
		len2 = ft_safe_strlen(s2);
	str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	str[len2 + len1] = '\0';
	while (len2--)
		str[len1 + len2] = s2[len2];
	while (len1--)
		str[len1] = s1[len1];
	free(s1);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sep_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:43:50 by acroue            #+#    #+#             */
/*   Updated: 2024/01/24 18:44:39 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_sep_join(char *s1, char *s2, char *sep)
{
	char	*res;
	int		len_s1;
	int		len_s2;
	int		sep_len;

	len_s1 = ft_safe_strlen(s1);
	len_s2 = ft_safe_strlen(s2);
	sep_len = ft_safe_strlen(sep);
	res = malloc((len_s1 + len_s2 + sep_len + 1) * sizeof(char));
	if (!res)
		return (free(s1), NULL);
	res[len_s1 + len_s2 + sep_len] = '\0';
	while (len_s2--)
		res[len_s1 + sep_len + len_s2] = s2[len_s2];
	while (sep_len--)
		res[len_s1 + sep_len] = sep[sep_len];
	while (len_s1--)
		res[len_s1] = s1[len_s1];
	free(s1);
	return (res);
}

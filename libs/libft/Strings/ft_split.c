/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:12:51 by acroue            #+#    #+#             */
/*   Updated: 2024/01/10 19:59:53 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_count_words(char const *s, char c)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			result++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (result);
}

static int	ft_next_sep(const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != sep)
	{
		i++;
	}
	return (i);
}

void	ft_free(char **split_array, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
	return ;
}

static char	*ft_strndup(char *src, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_calloc((n + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**split_array;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	split_array = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!split_array)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			split_array[j] = ft_strndup((char *)&s[i], ft_next_sep(&s[i], c));
			if (!split_array[j++])
				return (ft_free(split_array, j - 1), NULL);
			i += ft_next_sep(&s[i], c);
		}
	}
	split_array[j] = NULL;
	return (split_array);
}

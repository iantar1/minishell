/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 08:28:28 by iantar            #+#    #+#             */
/*   Updated: 2023/04/15 12:28:17 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_p(char const *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			n++;
		i++;
	}
	return (n);
}

static	int	len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static	char	**free_it(char **ptr, size_t j)
{
	while (j > 0)
		free(ptr[--j]);
	free(ptr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**ptr;
	size_t	j;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	ptr = malloc((count_p(s, c) + 1) * (sizeof(char *)));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			ptr[j] = ft_substr(s, (unsigned int)i, len(s + i, c));
			if (!ptr[j])
				return (free_it(ptr, j));
			i = i + len(s + i, c) - 1;
			j++;
		}
		i++;
	}
	ptr[j] = NULL;
	return (ptr);
}

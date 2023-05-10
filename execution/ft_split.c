/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:41:10 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/10 14:51:53 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"
#include<stdlib.h>

static size_t	len_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 1;
	count = 0;
	if (!s)
		return (0);
	if (s[0] != c && s[0])
		count++;
	while (i < oi_strlen((char *)s))
	{
		if (s[i - 1] == c && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static	int	allocate(char **strs, int index, size_t size)
{
	strs[index] = malloc(size);
	if (!strs[index])
	{
		while (index >= 0)
			free(strs[index--]);
		free(strs);
		return (0);
	}
	return (1);
}

static size_t	len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (c == 0 && s[i])
		i++;
	return (i);
}

char	**oi_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;

	i = 0;
	j = 0;
	if (!s || !s[0])
		return (0);
	strs = malloc((len_words(s, c) + 1) * sizeof(char *));
	while (j < len_words(s, c) && s[0])
	{
		k = 0;
		while (s[i] == c)
			i++;
		str = (char *)s + i;
		if (!allocate(strs, j, len(str, c) + 1))
			return (0);
		while (k < len(str, c))
			strs[j][k++] = s[i++];
		strs[j++][k] = 0;
	}
	return (strs[j] = NULL, strs);
}

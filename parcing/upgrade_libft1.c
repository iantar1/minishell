/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:41:04 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 18:01:04 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strdup_upgrade(const char *s1)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)upgrade_malloc((ft_strlen(s1) + 1) * sizeof(char), 0);
	if (!ptr)
		return (0);
	while (i < ft_strlen(s1))
	{
		ptr[i] = ((char *)s1)[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*substr_upgrade(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	if (!s)
		return (0);
	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	ptr = (char *)upgrade_malloc(len + 1, 0);
	if (!ptr)
		return (0);
	while (i < len && (s)[start + i])
	{
		ptr[i] = (s)[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static	int	is_illa(const char c, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(set))
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*strtrim_upgrade(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (0);
	if (!(*s1))
		return (strdup_upgrade(s1));
	i = 0;
	j = 0;
	j = ft_strlen(s1) - 1;
	while (is_illa(s1[i], set))
		i++;
	while (is_illa(s1[j], set) && j >= i)
		j--;
	return (substr_upgrade(s1, i, j - i + 1));
}

char	*strjoin_upgrade(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;	

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = (char *)upgrade_malloc(ft_strlen(s1) + ft_strlen(s2) + 1, 0);
	if (!ptr)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:22:50 by iantar            #+#    #+#             */
/*   Updated: 2022/10/23 08:58:56 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (0);
	if (!(*s1))
		return (ft_strdup(s1));
	i = 0;
	j = 0;
	j = ft_strlen(s1) - 1;
	while (is_illa(s1[i], set))
		i++;
	while (is_illa(s1[j], set) && j >= i)
		j--;
	return (ft_substr(s1, i, j - i + 1));
}

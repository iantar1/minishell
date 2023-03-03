/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:28:27 by iantar            #+#    #+#             */
/*   Updated: 2022/10/19 20:00:54 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (!ft_strncmp(haystack + i, needle, ft_strlen(needle))
			&& i + ft_strlen(needle) <= len)
			return ((char *)(haystack + i));
		i++;
	}
	return (0);
}

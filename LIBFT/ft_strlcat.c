/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:17:39 by iantar            #+#    #+#             */
/*   Updated: 2022/10/19 20:02:29 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lensrc;
	size_t	lendst;

	i = 0;
	lensrc = ft_strlen(src);
	if (dstsize == 0)
		return (lensrc);
	lendst = ft_strlen((const char *)dst);
	if (lendst >= dstsize)
		return (lensrc + dstsize);
	while (i < dstsize - lendst - 1 && src[i])
	{
		dst[i + lendst] = src[i];
		i++;
	}
	dst[i + lendst] = 0;
	return (lendst + lensrc);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:18:03 by iantar            #+#    #+#             */
/*   Updated: 2022/10/22 22:03:12 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	ptr = malloc(size * count);
	if (!ptr)
		return (0);
	i = 0;
	while (i < size * count)
		((unsigned char *)ptr)[i++] = 0;
	return (ptr);
}

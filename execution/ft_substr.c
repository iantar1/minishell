/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:29:24 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/13 11:05:50 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell_oi.h"

char	*oi_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	y;
	size_t	s_len;

	i = 0;
	y = start;
	if (!s)
		return (NULL);
	s_len = oi_strlen((char *)s);
	if (start > s_len)
		len = 0;
	else if (start + len > s_len)
		len = s_len - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (0);
	while (i < len && (y < s_len))
		ptr[i++] = s[y++];
	ptr[i] = 0;
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:21:20 by iantar            #+#    #+#             */
/*   Updated: 2023/02/25 20:30:57 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char **save_buf, char *buf, int len_buf)
{
	int		i;
	int		j;
	int		len;
	char	*rtn;

	i = 0;
	len = ft_strlen(*save_buf);
	rtn = malloc(len + len_buf + 1);
	if (!rtn)
		return (NULL);
	while (i < len)
	{
		rtn[i] = *(*save_buf + i);
		i++;
	}
	j = 0;
	while (j < len_buf)
		rtn[i++] = buf[j++];
	ft_free(save_buf);
	rtn[i] = '\0';
	return (rtn);
}

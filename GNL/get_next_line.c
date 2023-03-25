/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:21:04 by iantar            #+#    #+#             */
/*   Updated: 2023/02/25 20:48:20 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	there_new_line(char *save_buf)
{
	int	index;

	index = 0;
	while (save_buf[index])
	{
		if (save_buf[index] == '\n')
			return (index);
		index++;
	}
	return (-1);
}

char	*rtn_line(char **save_buf, int index)
{
	int		i;
	char	*rtn;
	char	*tmp;

	i = -1;
	rtn = malloc(sizeof(char) * (index + 2));
	while (++i <= index)
		rtn[i] = *(*save_buf + i);
	rtn[i] = '\0';
	tmp = malloc(ft_strlen(*save_buf) - index);
	i = 1;
	while (*(*save_buf + index + i))
	{
		tmp[i - 1] = *(*save_buf + index + i);
		i++;
	}
	tmp[i - 1] = '\0';
	ft_free(save_buf);
	*save_buf = tmp;
	return (rtn);
}

char	*rtn_and_clean(char **save_buf)
{
	char	*last_line;
	int		len;
	int		i;
	int		index;

	i = -1;
	if (!*save_buf || !**save_buf)
	{
		if (*save_buf)
			ft_free(save_buf);
		return (NULL);
	}
	index = there_new_line(*save_buf);
	if (index != -1)
		return (rtn_line(save_buf, index));
	len = ft_strlen(*save_buf);
	last_line = *save_buf;
	*save_buf = NULL;
	return (last_line);
}

void	ft_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save_buf;
	int			len;
	int			index;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	len = read(fd, buf, BUFFER_SIZE);
	while (len)
	{
		if (len == -1)
			return ((free(buf)), (ft_free(&save_buf)), NULL);
		buf[len] = '\0';
		save_buf = ft_strjoin(&save_buf, buf, len);
		index = there_new_line(save_buf);
		if (index != -1)
			return ((free(buf)), rtn_line(&save_buf, index));
		len = read(fd, buf, BUFFER_SIZE);
	}
	return ((free(buf)), rtn_and_clean(&save_buf));
}

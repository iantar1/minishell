/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:36:15 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/11 10:50:47 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

char	*free_oi(char **s1, char **s2)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = 0;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = 0;
	}
	return (0);
}

size_t	oi_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	find(char	*save_buf)
{
	size_t	i;

	i = 0;
	while (save_buf[i])
	{
		if (save_buf[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*oi_strdup(char *s1)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s1)
		return (0);
	ptr = (char *)malloc((oi_strlen(s1) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (i < oi_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

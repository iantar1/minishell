/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:52:08 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 17:52:33 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_ptr(char const *mark)
{
	int		i;
	int		n;
	char	old;

	i = 0;
	n = 0;
	old = '\0';
	while (mark[i])
	{
		if (mark[i] != '1' && mark[i] != old)
			n++;
		old = mark[i];
		i++;
	}
	return (n);
}

int	len(char const *mark)
{
	int		i;
	char	old;

	i = 0;
	old = mark[0];
	while (mark[i])
	{
		if (mark[i] != old)
			return (i);
		old = mark[i];
		i++;
	}
	return (i);
}

char	**free_it(char **ptr, size_t j)
{
	while (j > 0)
		free(ptr[--j]);
	free(ptr);
	return (0);
}

char	**upgrade_split(char *str, char *mark)
{
	size_t	i;
	char	**ptr;
	size_t	j;

	if (!str || !*str)
		return (NULL);
	i = 0;
	j = 0;
	ptr = upgrade_malloc((count_ptr(mark) + 1) * (sizeof(char *)), 0);
	if (!ptr)
		return (free(str), NULL);
	while (mark[i])
	{
		if (mark[i] != 49)
		{
			ptr[j] = substr_upgrade(str, (unsigned int)i, len(&*(mark + i)));
			if (!ptr[j])
				return (free_it(ptr, j));
			i = i + len(&*(mark + i)) - 1;
			j++;
		}
		i++;
	}
	ptr[j] = NULL;
	return (ptr);
}

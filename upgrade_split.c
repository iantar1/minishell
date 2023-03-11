/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:52:08 by iantar            #+#    #+#             */
/*   Updated: 2023/03/07 11:39:13 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"

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

	if (!str)
		return (0);
	i = 0;
	j = 0;
	ptr = malloc((count_ptr(mark) + 1) * (sizeof(char *)));
	if (!ptr)
		return (0);
	while (mark[i])
	{
		if (mark[i] != 49)
		{
			ptr[j] = ft_substr(str, (unsigned int)i, len(&*(mark + i)));
			if (!ptr[j])
				return (free_it(ptr, j));
			i = i + len(&*(mark + i)) - 1;
			j++;
		}
		i++;
	}
	ptr[j] = NULL;
	return (free(mark), ptr);
}

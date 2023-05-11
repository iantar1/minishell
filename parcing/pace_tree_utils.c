/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pace_tree_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:39:45 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 15:39:59 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_oi.h"

int	need_split(char *mark)
{
	int		i;
	char	c;

	i = 0;
	c = mark[i];
	while (mark[++i])
		if (mark[i] != c)
			return (1);
	return (0);
}

void	mark_the_pipe_mark(char *mark)
{
	int	len;
	int	check;

	len = ft_strlen(mark);
	check = 1;
	while (--len >= 0)
	{
		if (mark[len] == '2' && check)
			check = 0;
		else if (mark[len] == '2')
			mark[len] = '0';
	}
}

void	mark_the_red_mark(char *mark)
{
	int	len;
	int	check;

	len = ft_strlen(mark);
	check = 1;
	while (--len >= 0)
	{
		if (mark[len] == '2' && check)
		{
			check = 0;
			if (len && mark[len - 1] == '2')
				len--;
		}
		else if (mark[len] == '2')
			mark[len] = '0';
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthisis_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:02:29 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 16:04:30 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_mark1(char *mark, int *check, int i)
{
	if (!*check)
		mark[i] = '1';
	else
		mark[i] = '0';
	(*check)++;
}

void	fill_mark2(char *mark, int *check, int i)
{
	if (*check == 1)
		mark[i] = '1';
	else
		mark[i] = '0';
	(*check)--;
}

char	*mark_first_parenthisis(char *str)
{
	int		check;
	int		i;
	char	*mark;
	int		flag;

	mark = upgrade_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
	i = -1;
	check = 0;
	flag = 0;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (str[i] == '(' && !flag)
			fill_mark1(mark, &check, i);
		else if (str[i] == ')' && !flag)
			fill_mark2(mark, &check, i);
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
}

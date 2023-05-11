/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction_handle_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:44:56 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 15:48:09 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*red_mark(char *str, int sp)
{
	int		i;
	int		flag;
	char	*mark;

	i = 0;
	flag = 0;
	mark = upgrade_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
	while (str[i])
	{
		ft_flag(str[i], &flag);
		if (!flag && str[i] == '>')
			mark[i] = '2';
		else if (!flag && str[i] == '<')
			mark[i] = '3';
		else if (str[i] <= 32 && str[i] > 0 && sp && !flag)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

void	ft_swap(char **ref1, char **ref2)
{
	char	*tmp;

	tmp = *ref1;
	*ref1 = *ref2;
	*ref2 = tmp;
}

int	count_red(char **splt, char *red)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (splt[i])
	{
		if (!ft_strcmp(splt[i], red))
			cnt++;
		i++;
	}
	return (cnt);
}

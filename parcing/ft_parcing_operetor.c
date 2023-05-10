/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing_operetor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:25:43 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 16:56:37 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_here_needle(char *str, char *needle)
{
	int	i;

	i = 0;
	if (!str || !needle)
		return (0);
	while (str[i])
	{
		if (!ft_strncmp(str + i, needle, ft_strlen(needle)))
			return (1);
		i++;
	}
	return (0);
}

void	inside_paranth(char c, char *inside, int flag)
{
	if (c == '(' && !flag)
		(*inside)++;
	if (c == ')' && !flag)
		(*inside)--;
}

void	fill_mark_oper(char *str, int check, char *mark, int sp)
{
	int	i;
	int	flag;
	char	inside;

	i = -1;
	flag = 0;
	inside = 0;
	(void)check;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		inside_paranth(str[i], &inside, flag);
		if ((str[i] == '|' || str[i] == '&') && !flag && !inside)
			mark[i] = '2';
		else if (str[i] <= 32 &&  str[i] > 0 && sp && !flag && !inside)
			mark[i] = '1';
		else
			mark[i] = '0';
		// if (str[i] == 34 || str[i] == 39)
		// {
		// 	if (str[i] == check)
		// 		check = 0;
		// 	else if (!check)
		// 		check = str[i];
		// }
		// if (!check && str[i] == '(')
		// 	check = str[i];
		// if (check == '(' && str[i] == ')')
		// 	check = 0;
		// if ((str[i] == '|' || str[i] == '&') && !check)
		// 	mark[i] = '2';
		// else if (!check && str[i] <= 32 &&  str[i] > 0 && sp)
		// 	mark[i] = '1';
		// else
		// 	mark[i] = '0';
	}
	mark[i] = '\0';
}

char	*ft_mark_operator(char *str, int sp)
{
	char	*mark;
	char	check;

	if (!str || !*str)
		return (NULL);
	mark = upgrade_malloc(sizeof(char) * ft_strlen(str) + 1, 0);
	check = 0;
	fill_mark_oper(str, check, mark, sp);
	return (mark);
}

char	*mark_the_mark_operator(char *mark)
{
	int		len;
	int		check;

	if (!mark)
		return (NULL);
	len = ft_strlen(mark) - 1;
	check = 1;
	while (len >= 0)
	{
		if (len && (mark[len] == '2' && mark[len - 1] == '2') && check)
		{
			mark[len--] = '2';
			mark[len--] = '2';
			check = 0;
		}
		else
			mark[len--] = '0';
	}
	return (mark);
}

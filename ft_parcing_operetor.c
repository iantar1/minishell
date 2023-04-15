/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing_operetor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:25:43 by iantar            #+#    #+#             */
/*   Updated: 2023/04/15 02:36:56 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_mark_operator(char *str, int sp)
{
	int		i;
	char	*mark;
	char	check;

	if (!str || !*str)
		return (NULL);
	mark = malloc(sizeof(char) * ft_strlen(str) + 1);
	check = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (str[i] == check)
				check = 0;
			else if (!check)
				check = str[i];
		}
		if (!check && str[i] == '(')
			check = str[i];
		if (check == '(' && str[i] == ')')
			check = 0;
		if ((str[i] == '|' || str[i] == '&') && !check)
			mark[i] = '2';
		else if (!check && mark[i] <= 32 && sp)//nw
			mark[i] = '1';
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
}
//you must check the syntax error befor using this function, str must not start with | or &. or has '|&'
char	*mark_the_mark_operator(char *mark)//split with the last && or ||
{
	int		len;
	int		check;

	len = ft_strlen(mark) - 1;
	check = 1;
	while (len >= 0)
	{
		if ((mark[len] == '2' && mark[len - 1] == '2') && check)
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

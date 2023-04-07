/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:22:47 by iantar            #+#    #+#             */
/*   Updated: 2023/04/07 02:20:57 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_mark(char *str)//use it to check the syntax.
{
	int		i;
	char	*mark;
	int		check1;
	int		check2;

	if (!str)
		return (NULL);
	mark = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!mark)
		return (NULL);
	i = -1;
	check1 = 0;
	check2 = 0;
	while (str[++i])
	{
		if (str[i] == 34)
		{
			check1++;
			mark[i] = '0';
		}
		if (str[i] == 39)
		{
			check2++;
			mark[i] = '0';
		}
		else if (check1 % 2)
			mark[i] = '0';
		else if (check2 % 2)
			mark[i] = '0';
		else if (str[i] == '&' || str[i] == '|')
			mark[i] = '2';
		else if (str[i] == '>' || str[i] == '<')
			mark[i] = '3';
		else if (str[i] == '*')
			mark[i] = '4';
		else if (str[i] > 32)
			mark[i] = '0';
		else
			mark[i] = '1';
	}
	mark[i] = '\0';
	return (mark);
}

char	closed_quote(char *str)
{
	int		i;
	int		check1;
	int		check2;
	char	first;

	i = -1;
	check1 = 0;
	check2 = 0;
	first = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == 34 && ++check1)
		{
			if (first == 34)
			{
				first = 0;
				check1 = 0;
				check2 = 0;
			}
			else if (first == 0)
				first = 34;
		}
		if (str[i] == 39 && ++check2)
		{
			if (first == 39)
			{
				first = 0;
				check1 = 0;
				check2 = 0;
			}
			else if (first == 0)
				first = 39;
		}
	}
	if (!(check1 % 2) && first == 34)
		return (34);
	if ((!(check2 % 2) && first == 39) || (!check1 && !check2))
		return (39);
	return (0);
}

char	*remove_quote(char *str)
{
	int		first;
	int		i;
	char	*rtn;
	t_list	*lst;
	t_list	*tmp;

	if (!str || !*str)
		return (NULL);
	i = -1;
	first = 0;
	lst = ft_lstnew("0");
	tmp = lst;
	while (str[++i])
	{
		if (str[i] == 34 && (!first || first == 34))
		{
			if (first == 34)
				first = 0;
			else
				first = 34;
			continue ;
		}
		if (str[i] == 39 && (!first || first == 39))
		{
			if (first == 39)
				first = 0;
			else
				first = 39;
			continue ;
		}
		tmp->next = ft_lstnew(&str[i]);
		tmp = tmp->next;
	}
	tmp = lst;
	lst = lst->next;
	rtn = malloc(sizeof(char) * ft_lstsize(lst) + 1);
	i = -1;
	while (++i < ft_lstsize(tmp) - 1)
	{
		rtn[i] = *(char *)(lst->content);
		lst = lst->next;
	}
	rtn[i] = '\0';
	return (rtn);
}

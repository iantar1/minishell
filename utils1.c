/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:22:47 by iantar            #+#    #+#             */
/*   Updated: 2023/05/01 15:47:38 by iantar           ###   ########.fr       */
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
		else if (str[i] == '&')
			mark[i] = '2';
		else if (str[i] == '>' || str[i] == '<')
			mark[i] = '3';
		// else if (str[i] == '*')
		// 	mark[i] = '4';
		else if (str[i] == '|')
			mark[i] = '5';
		else if (str[i] <= 32)
			mark[i] = '1';
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
}

char	unclosed_quote(char *str)
{
	int		i;
	char	check;

	i = -1;
	check = 0;
	while (str[++i])
	{
		if (str[i] == 34 && check != 39)
		{
			if (check == 34)
				check = 0;
			else
				check = 34;
		}
		if (str[i] == 39 && check != 34)
		{
			if (check == 39)
				check = 0;
			else
				check = 39;
		}
	}
	return (check);
}

char	*remove_quote(char *str)
{
	int		first;
	int		i;
	char	*rtn;
	t_list	*lst;
	t_list	*tmp;

	if (!str)
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
	while (tmp)
	{
		lst = tmp;
		tmp = tmp->next;
		free(lst);
	}
	return (rtn);
}

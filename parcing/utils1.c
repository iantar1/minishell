/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:22:47 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 16:58:47 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_mark(char *str)
{
	int		i;
	char	*mark;
	int		flag;

	if (!str)
		return (NULL);
	mark = upgrade_malloc(sizeof(char) * ft_strlen(str) + 1, 0);
	i = -1;
	flag = 0;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (str[i] <= 32 && str[i] > 0 && !flag)
			mark[i] = '1';
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
}

char	unclosed_quote(char *str)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (str[++i])
		ft_flag(str[i], &check);
	return ((char)check);
}

t_list	*get_removed_quote_list(char *str)
{
	int		first;
	int		i;
	t_list	*lst;
	t_list	*tmp;

	i = -1;
	first = 0;
	lst = ft_lstnew("0");
	tmp = lst;
	while (str && str[++i])
	{
		ft_flag(str[i], &first);
		if (str[i] == 34 && (!first || first == 34))
			continue ;
		if (str[i] == 39 && (!first || first == 39))
			continue ;
		tmp->next = ft_lstnew(&str[i]);
		tmp = tmp->next;
	}
	return (lst);
}

char	*remove_quote(char *str)
{
	int		i;
	char	*rtn;
	t_list	*lst;
	t_list	*tmp;

	if (!str)
		return (NULL);
	lst = get_removed_quote_list(str);
	tmp = lst;
	lst = lst->next;
	rtn = upgrade_malloc(sizeof(char) * ft_lstsize(lst) + 1, 0);
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

//$USER$
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:55:42 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 15:57:34 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*lst_to_str_wirld(t_list *lst)
{
	int		i;
	char	*str;
	char	*tmp_str;
	t_list	*tmp;

	i = 0;
	if (!lst)
		return (NULL);
	tmp = lst;
	str = tmp->content;
	tmp = tmp->next;
	while (tmp)
	{
		if (!(tmp->content))
			return (str);
		tmp_str = str;
		str = strjoin_upgrade(str, " ");
		tmp_str = str;
		str = strjoin_upgrade(str, tmp->content);
		tmp = tmp->next;
	}
	return (str);
}

char	*edit_mark(char *mark)
{
	int		i;
	char	*new_mark;

	if (!mark)
		return (mark);
	i = -1;
	new_mark = upgrade_malloc(ft_strlen(mark) + 1, 0);
	while (mark && mark[++i])
	{
		if (mark[i] == '4')
			new_mark[i] = '0';
		else
			new_mark[i] = mark[i];
	}
	new_mark[i] = '\0';
	return (new_mark);
}

int	is_wildcard(char *mark)
{
	int	i;

	i = 0;
	if (!mark)
		return (0);
	while (mark[i])
	{
		if (mark[i] == '9')
			return (1);
		i++;
	}
	return (0);
}

char	*mark_wildcard(char *str)
{
	int		i;
	int		flag;
	char	*mark;

	i = 0;
	flag = 0;
	if (!str)
		return (NULL);
	mark = upgrade_malloc(ft_strlen(str) * sizeof(char) + 1, 0);
	while (str[i])
	{
		ft_flag(str[i], &flag);
		if (str[i] == '*' && !flag)
			mark[i] = '9';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

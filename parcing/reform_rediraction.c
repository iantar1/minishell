/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reform_rediraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:45:25 by iantar            #+#    #+#             */
/*   Updated: 2023/11/10 21:50:38 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	index_of_1st_redir(t_list *lst)
{
	int	index;

	index = 0;
	lst = lst->next;
	while (lst)
	{
		if (!ft_strncmp(lst->content, ">", 1)
			|| !ft_strncmp(lst->content, "<", 1))
			return (index);
		index++;
		lst = lst->next;
	}
	return (-1);
}

void	reform_it(t_list **lst)
{
	t_vars	var;

	var.len = count_redirect(*lst);
	var.tmp1 = *lst;
	while (var.len)
	{
		var.index = index_of_1st_redir(*lst);
		var.i = -1;
		var.tmp1 = *lst;
		while (++(var.i) < var.index)
			var.tmp1 = var.tmp1->next;
		var.tmp2 = var.tmp1->next;
		if (var.tmp2->next)
		{
			var.tmp1->next = var.tmp2->next->next;
			var.tmp2->next->next = NULL;
		}
		else
			var.tmp1->next = var.tmp2->next;
		ft_lstadd_back(lst, var.tmp2);
		(var.len)--;
	}
	var.tmp1 = *lst;
	*lst = (*lst)->next;
}

char	*lst_to_str(t_list *lst)
{
	t_list	*tmp;
	char	*str;

	tmp = lst;
	str = strdup_upgrade(lst->content);
	tmp = tmp->next;
	while (tmp)
	{
		str = strjoin_upgrade(str, " ");
		str = strjoin_upgrade(str, tmp->content);
		tmp = tmp->next;
	}
	return (str);
}

char	there_is_red(char *mark)
{
	int		i;

	i = -1;
	while (mark && mark[++i])
		if (mark[i] == '2')
			return (1);
	return (0);
}

char	*reform_redirection(char *str)
{
	char	**splt_cmd;
	char	*rtn_str;
	char	*mark;
	t_list	*lst;

	mark = mark_redirection(str, SPACE);
	if (!there_is_red(mark))
		return (strdup_upgrade(str));
	splt_cmd = upgrade_split(str, mark);
	lst = arr_to_lst(splt_cmd);
	reform_it(&lst);
	rtn_str = lst_to_str(lst);
	return (rtn_str);
}

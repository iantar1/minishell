/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reform_rediraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:45:25 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 20:19:47 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lst(t_list *lst)
{
	t_list	*back;

	while (lst)
	{
		back = lst;
		if (lst->content)
			free(lst->content);
		lst = lst->next;
		free(back);
	}
}

void	ft_flag(char c, int *flag)
{
	if (c == 34 && *flag != 39)
	{
		if (!*flag)
			*flag = 34;
		else
			*flag = 0;
	}
	if (c == 39 && *flag != 34)
	{
		if (!*flag)
			*flag = 39;
		else
			*flag = 0;
	}
}

char	*mark_redirection(char *str, int sp)
{
	int		i;
	int		flag;
	char	*mark;
	char	inside;

	i = 0;
	flag = 0;
	inside = 0;
	mark = upgrade_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
	while (str[i])
	{
		ft_flag(str[i], &flag);
		inside_paranth(str[i], &inside, flag);
		if (!inside && !flag && (str[i] == '>' || str[i] == '<'))
			mark[i] = '2';
		else if (str[i] <= 32 && str[i] >= 0 && sp && !flag && !inside)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

// char	**lst_to_arr(t_list *lst)
// {
// 	int		i;
// 	char	**str;
// 	t_list	*tmp;

// 	i = 0;
// 	tmp = lst;
// 	str = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
// 	while (lst)
// 	{
// 		str[i++] = ft_strdup(lst->content);
// 		lst = lst->next;
// 	}
// 	str[i] = NULL;
// 	ft_lstclear(&tmp, free);
// 	return (str);
// }

t_list	*arr_to_lst(char **str)
{
	int		i;
	t_list	*tmp;
	t_list	*lst;

	i = 0;
	lst = ft_lstnew(NULL);
	tmp = lst;
	while (str[i])
	{
		lst->next = ft_lstnew(strdup_upgrade(str[i]));
		lst = lst->next;
		i++;
	}
	return (tmp);
}

int	count_redirect(t_list *lst)
{
	int	count;

	count = 0;
	lst = lst->next;
	while (lst)
	{
		if (!ft_strncmp(lst->content, ">", 1)
			|| !ft_strncmp(lst->content, "<", 1))
			count++;
			lst = lst->next;
	}
	return (count);
}

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

void	reform_it(t_list **lst)//you must read this fun again
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
			var.tmp1->next = var.tmp2->next->next;//here the problem
			var.tmp2->next->next = NULL;//and here too
		}
		else
			var.tmp1->next = var.tmp2->next;//here the problem+
		ft_lstadd_back(lst, var.tmp2);
		(var.len)--;
	}
	var.tmp1 = *lst;
	*lst = (*lst)->next;
	free(var.tmp1);
}

char	*lst_to_str(t_list *lst)
{
	t_list	*tmp;
	char	*str;
	char	*to_free;
	int		i;

	i = 0;
	tmp = lst;
	str = strdup_upgrade(lst->content);
	tmp = tmp->next;
	while (tmp)
	{
		to_free = str;
		str = strjoin_upgrade(str, " ");
		free(to_free);
		to_free = str;
		str = strjoin_upgrade(str, tmp->content);
		free(to_free);
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
		return (free(mark), strdup_upgrade(str));
	splt_cmd = upgrade_split(str, mark);
	lst = arr_to_lst(splt_cmd);
	reform_it(&lst);
	rtn_str = lst_to_str(lst);
	free_lst(lst);
	free_ptr(splt_cmd);
	return (free(mark), rtn_str);
}

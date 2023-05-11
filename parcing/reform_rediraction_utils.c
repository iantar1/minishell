/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reform_rediraction_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:19:23 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 16:21:04 by iantar           ###   ########.fr       */
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

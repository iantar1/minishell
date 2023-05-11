/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upgrade_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:55:22 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 21:01:43 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*upgrade_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (0);
	ptr -> content = content;
	ptr -> next = NULL;
	return (ptr);
}

void	*upgrade_malloc(size_t size, int to_free)
{
	static t_list	*lst;
	t_list			*tmp;
	void			*rtn;

	tmp = lst;
	if (to_free)
	{
		if (lst)
			free_lst(lst);
		lst = NULL;
		return (NULL);
	}
	rtn = malloc(size);
	if (!lst)
		lst = upgrade_lstnew(rtn);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = upgrade_lstnew(rtn);
	}
	return (rtn);
}

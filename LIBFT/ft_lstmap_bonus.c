/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:38:23 by iantar            #+#    #+#             */
/*   Updated: 2022/10/23 22:29:57 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*q;

	if (!lst || !f || !del)
		return (0);
	p = ft_lstnew(f(lst->content));
	if (!p)
		return (0);
	lst = lst->next;
	while (lst)
	{
		q = ft_lstnew(f(lst->content));
		if (!q)
		{
			ft_lstclear(&p, del);
			return (0);
		}
		ft_lstadd_back(&p, q);
		lst = lst->next;
	}
	return (p);
}

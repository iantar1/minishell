/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:50:18 by iantar            #+#    #+#             */
/*   Updated: 2023/02/21 18:40:31 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"

void	*ft_malloc(int size, t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	if (!*head)
		*head = ft_listnew(malloc(size));
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_listnew(malloc(size));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:50:18 by iantar            #+#    #+#             */
/*   Updated: 2023/04/15 00:29:12 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"

void	*ft_malloc(int size, t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->content = malloc(size);
	return (tmp->content);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:13:00 by iantar            #+#    #+#             */
/*   Updated: 2023/02/23 15:32:23 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*ft_tree_new(void *content, t_tree *parent)
{
	t_tree	*ptr;

	ptr = (t_tree *)malloc(sizeof(t_tree));
	if (!ptr)
		return (0);
	ptr->content = content;
	ptr->right_child = NULL;
	ptr->left_child = NULL;
	return (ptr);
}
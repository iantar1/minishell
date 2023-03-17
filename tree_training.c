/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_training.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:32:29 by iantar            #+#    #+#             */
/*   Updated: 2023/03/17 10:45:06 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_data
{
	struct s_data	*next;
	void			**content;
	char			type;//O:Operator(&& || |),  C:Commad, 
}t_data;

t_data	*ft_new_knot(void **content)
{
	t_data	*ptr;

	ptr = (t_data *)malloc(sizeof(t_data));
	if (!ptr)
		return (0);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

typedef struct s_tree
{
	struct s_tree	*right_child;
	struct s_tree	*left_child;
	//struct s_tree	*parent;
	//t_data			*data;
	void			**content;
}t_tree;


t_tree	*ft_new_knot(void **content)
{
	t_tree	*ptr;

	ptr = (t_tree *)malloc(sizeof(t_tree));
	if (!ptr)
		return (0);
	ptr->content = content;
	ptr->left_child = NULL;
	ptr->right_child = NULL;
	return (ptr);
}

void	parce_tree(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree->content[i])
	{
		if (is_com)
	}
}

int	main(int ac, char *av[])
{
	int		i;
	char	*content[4];
	t_tree	*tree;

	content = {"ls", "&&", "ls", NULL};
	tree  = ft_new_knot(content);

}

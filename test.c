/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:15:39 by iantar            #+#    #+#             */
/*   Updated: 2023/03/01 12:57:59 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_tree
{
	void	*parent;
	void	*right_child;
	void	*left_child;
	void	*content;
}t_tree;

int	main(void)
{
	// char	*cmd[] = {"ls", NULL};
	// char	*path = "/bin/mkdir";
	int	i;

	i = 0;
	// execve(path, cmd, NULL);
	if (1 && ++i)
		printf("yy\n");
	return (0);
}
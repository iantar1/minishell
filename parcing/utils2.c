/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:24:56 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 20:04:09 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	free_tree(tree->left_c);
	free_tree(tree->right_c);
	if (tree->data.cmd)
		free(tree->data.cmd);
	free_ptr(tree->data.args);
	free(tree);
}

char	**get_env(char **env)
{
	char	**save_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	save_env = (char **)upgrade_malloc(sizeof(char *) * (i + 1), 0);
	if (!save_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		save_env[i] = strdup_upgrade(env[i]);
		i++;
	}
	save_env[i] = NULL;
	return (save_env);
}

void	free_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (i > 0)
		free(ptr[i]);
	free(ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:24:56 by iantar            #+#    #+#             */
/*   Updated: 2023/03/29 22:18:54 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"

char	**get_env(char **env)
{
	char	**save_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	save_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!save_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		save_env[i] = ft_strdup(env[i]);
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
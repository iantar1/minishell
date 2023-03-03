/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:24:56 by iantar            #+#    #+#             */
/*   Updated: 2023/03/01 10:43:37 by iantar           ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:24:56 by iantar            #+#    #+#             */
/*   Updated: 2023/11/10 21:46:29 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

unsigned char	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	handle_sig(int sig)
{
	(void)sig;
	exit(1);
}

char	*arr_to_str(char **splt)
{
	int		i;
	char	*str;

	if (!splt || !*splt)
		return (NULL);
	i = 0;
	str = splt[i];
	while (splt[++i])
	{
		str = strjoin_upgrade(str, " ");
		str = strjoin_upgrade(str, splt[i]);
	}
	str = strtrim_upgrade(str, "	 ");
	return (str);
}

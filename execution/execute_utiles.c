/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 00:33:55 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/10 14:51:09 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

void	from_list_char_complete(char **strs, int *k)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (g_env->var_name && g_env->var_name[j])
		strs[(*k)][i++] = g_env->var_name[j++];
	j = 0;
	strs[(*k)][i++] = '=';
	while (g_env->line && g_env->line[j])
		strs[(*k)][i++] = g_env->line[j++];
	strs[(*k)++][i] = '\0';
	g_env = g_env->next;
}

char	**from_list_to_char(int check)
{
	static char	**strs;
	int			k;
	t_env		*tmp;

	if (strs && !check)
		return (strs);
	k = 0;
	tmp = g_env;
	strs = malloc((list_size() + 1) * sizeof(char *));
	while (g_env)
	{
		if (!oi_strcmp(g_env->var_name, "?"))
		{
			g_env = g_env->next;
			continue ;
		}
		strs[k] = malloc((oi_strlen(g_env->var_name)
					+ oi_strlen(g_env->line) + 2) * sizeof(char));
		from_list_char_complete(strs, &k);
	}
	return (g_env = tmp, strs[k] = NULL, strs);
}

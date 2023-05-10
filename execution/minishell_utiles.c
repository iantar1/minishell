/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:28:28 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/10 14:52:04 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

size_t	list_size(void)
{
	size_t	i;
	t_env	*tmp;

	i = 0;
	tmp = g_env;
	while (g_env)
	{
		g_env = g_env->next;
		i++;
	}
	g_env = tmp;
	return (i);
}

char	**sort_vars(char	**strs, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (oi_strcmp(strs[i], strs[j]) > 0)
			{
				tmp = oi_strdup(strs[i]);
				free(strs[i]);
				strs[i] = oi_strdup(strs[j]);
				free(strs[j]);
				strs[j] = oi_strdup(tmp);
				free(tmp);
			}
			j++;
		}
		i++;
	}
	return (strs);
}

int	is_in_env(char	*var)
{
	t_env	*tmp;

	tmp = g_env;
	while (var && g_env)
	{
		if (!oi_strcmp(var, g_env->var_name))
		{
			g_env = tmp;
			return (1);
		}
		g_env = g_env->next;
	}
	g_env = tmp;
	return (0);
}

void	print_line(char *var)
{
	t_env	*tmp;

	if (!oi_strcmp(var, "?"))
		return ;
	tmp = g_env;
	while (g_env)
	{
		if (!oi_strcmp(var, g_env->var_name) && oi_strcmp(var, "_"))
		{
			ft_dprintf(1, "declare -x %s", g_env->var_name);
			if (g_env->line)
				ft_dprintf(1, "=\"%s\"\n", g_env->line);
			else
				ft_dprintf(1, "\n");
			break ;
		}
		g_env = g_env->next;
	}
	g_env = tmp;
}

int	show_env_in_order(void)
{
	size_t	len;
	char	**strs;
	size_t	i;
	t_env	*send;

	len = list_size();
	strs = malloc((len + 1) * sizeof(char *));
	i = 0;
	send = g_env;
	while (i < len)
	{
		strs[i++] = oi_strdup(g_env->var_name);
		g_env = g_env->next;
	}
	g_env = send;
	strs[i] = NULL;
	sort_vars(strs, i);
	i = -1;
	while (strs[++i])
		(print_line(strs[i]), free(strs[i]));
	free(strs);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:12:40 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/10 14:51:42 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

char	*ft_strndup(char *s1, unsigned int n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!s1)
		return (0);
	ptr = (char *)malloc((n + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (s1[i] && i < n)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**get_key_value_oi(char	*str)
{
	char	**key_value;
	int		i;
	char	*tmp;
	char	*val;

	i = 0;
	if (!str)
		return (NULL);
	key_value = malloc(3 * sizeof(char *));
	while (str[i] && str[i] != '=')
		i++;
	key_value[0] = oi_substr(str, 0, i);
	if (str[i])
	{
		tmp = oi_substr(str, i + 1, oi_strlen(str));
		val = parse_value(tmp);
		key_value[1] = oi_strdup(val);
		key_value[2] = (free(val), NULL);
	}
	else
		key_value[1] = NULL;
	return (key_value);
}

int	append_val(char *val)
{
	char	*data;
	t_env	*tmp;

	if (!val)
		return (0);
	tmp = g_env;
	data = classic_ft_strjoin(g_env->line, val);
	if (g_env->line)
		free(g_env->line);
	g_env->line = oi_strdup(data);
	free(data);
	g_env = tmp;
	return (0);
}

int	modify_var(char **var)
{
	char	*trim;
	t_env	*head;

	head = g_env;
	while (g_env)
	{
		trim = oi_strtrim(var[0], "+");
		if (!oi_strcmp(trim, g_env->var_name))
		{
			if (var[0][oi_strlen(var[0]) - 1] == '+')
				append_val(var[1]);
			else
			{
				((g_env->line) && (free(g_env->line), 0));
				g_env->line = oi_strdup(var[1]);
			}
			return (g_env = head, free(trim), 1);
		}
		free(trim);
		g_env = g_env->next;
	}
	if (trim)
		free(trim);
	return (g_env = head, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:38:49 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 14:28:26 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_free_(char **str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (1);
}

char	**get_key_value(char *str)
{
	char	**key_value;
	int		len_key;

	if (!str)
		return (NULL);
	key_value = upgrade_malloc(sizeof(char *) * 3, 0);
	len_key = 0;
	while (str[len_key] && str[len_key] != '=')
		len_key++;
	key_value[0] = substr_upgrade(str, 0, len_key);
	key_value[1] = strdup_upgrade(str + len_key + 1);
	key_value[2] = NULL;
	return (key_value);
}

size_t	len_double_char(char **strs)
{
	size_t	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

t_env	*new_line(char *line)
{
	t_env	*node;
	char	**str;
	char	*trimed;
	int		i;

	i = 0;
	str = get_key_value(line);
	node = upgrade_malloc(sizeof(t_env), 0);
	trimed = strtrim_upgrade(str[0], "+");
	node->var_name = strdup_upgrade(trimed);
	if (len_double_char(str) == 2)
		node->line = strdup_upgrade(str[1]);
	else if (len_double_char(str) == 1)
		node->line = NULL;
	node->next = NULL;
	return (node);
}

t_env	*create_env(char **env)
{
	t_env	*head;
	t_env	*tmp;
	int		i;

	i = 0;
	head = new_line(env[i++]);
	tmp = head;
	while (env[i])
	{
		head->next = new_line(env[i++]);
		head = head->next;
	}
	head = tmp;
	return (head);
}

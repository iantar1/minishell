/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:38:49 by iantar            #+#    #+#             */
/*   Updated: 2023/03/02 18:36:02 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free(char **str)
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
	key_value = malloc(sizeof(char *) * 3);
	len_key = 0;
	while (str[len_key] && str[len_key] != '=')
		len_key++;
	key_value[0] = ft_substr(str, 0, len_key);
	key_value[1] = ft_strdup(str + len_key + 1);
	key_value[2] = NULL;
	//free(str);
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
	node = malloc(sizeof(t_env));
	trimed = ft_strtrim(str[0], "+");
	node->var_name = ft_strdup(trimed);
	if (len_double_char(str) == 2)
		node->line = ft_strdup(str[1]);
	else if (len_double_char(str) == 1)
		node->line = NULL;
	node->next = NULL;
	return (free(trimed), ft_free(str), node);
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

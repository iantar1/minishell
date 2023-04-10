/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:01:01 by oidboufk          #+#    #+#             */
/*   Updated: 2023/04/02 03:20:28 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	complet_filter(char *str, char *elem, char *mask, int check)
{
	int	i;

	if (str[1] == '\0')
		return (1);
	i = -1;
	while (elem[++i])
	{
		if (is_in_filter(str + 1, elem + i, mask + 1, check + 1))
			return (1);
	}
	return (0);
}

int	is_in_filter(char *str, char *elem, char *mask, int check)
{
	int	st;

	if (*str != '.' && *elem == '.' && !check)
		return (0);
	else if (*str == '\0' && *elem == '\0')
		return (1);
	else if (*str == '*' && *mask == '9')
		return (complet_filter(str, elem, mask, check));
	else if (*str == '\0' || *elem == '\0')
		return (0);
	else if (*str == *elem || (*str == '*' && *mask == '9'))
	{
		st = is_in_filter(str + 1, elem + 1, mask + 1, check + 1);
		if (!st)
			st = is_in_filter(str, elem + 1, mask, check + 1);
		return (st);
	}
	return (0);
}

t_list	*new_node(char *data)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

t_list	*expand_wildcard(char *to_change, char *mask)
{
	t_list			*head;
	struct dirent	*dir_ent;
	t_list			*tmp;
	DIR				*dir;

	dir = opendir(".");
	dir_ent = readdir(dir);
	head = new_node(ft_strdup("."));
	tmp = head;
	while (dir_ent)
	{
		if (is_in_filter(to_change, dir_ent->d_name, mask, 0))
		{
			head->next = new_node(strdup(dir_ent->d_name));
			head = head->next;
		}
		dir_ent = readdir(dir);
	}
	head = tmp;
	(free_it(&head->data, 0), free(head));
	head = tmp->next;
	closedir(dir);
	if (!head)
		head = new_node(strdup(to_change));
	return (head);
}

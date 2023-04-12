/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:01:01 by oidboufk          #+#    #+#             */
/*   Updated: 2023/04/12 06:50:52 by iantar           ###   ########.fr       */
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
	node->content = data;
	node->next = NULL;
	return (node);
}

char	*free_it_(char **s1, char **s2)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = 0;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = 0;
	}
	return (0);
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
			head->next = new_node(ft_strdup(dir_ent->d_name));
			head = head->next;
		}
		dir_ent = readdir(dir);
	}
	head = tmp;
	(free_it_(((char **)(&head->content)), 0), free(head));
	head = tmp->next;
	closedir(dir);
	if (!head)
		head = new_node(ft_strdup(to_change));
	return (head);
}

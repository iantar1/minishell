/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:01:01 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/11 15:57:24 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	node = upgrade_malloc(sizeof(t_list), 0);
	if (!node)
		return (NULL);
	node->content = data;
	node->next = NULL;
	return (node);
}

// char	*free_it_(char **s1, char **s2)
// {
// 	if (s1 && *s1)
// 	{
// 		free(*s1);
// 		*s1 = 0;
// 	}
// 	if (s2 && *s2)
// 	{
// 		free(*s2);
// 		*s2 = 0;
// 	}
// 	return (0);
// }

t_list	*expand_wildcard(char *to_change, char *mask)
{
	t_list			*head;
	struct dirent	*dir_ent;
	t_list			*tmp;
	DIR				*dir;
	char			*strdup_;

	dir = opendir(".");
	dir_ent = readdir(dir);
	strdup_ = strdup_upgrade(".");
	head = new_node(strdup_);
	tmp = head;
	while (dir_ent)
	{
		if (is_in_filter(to_change, dir_ent->d_name, mask, 0))
		{
			head->next = new_node(strdup_upgrade(dir_ent->d_name));
			head = head->next;
		}
		dir_ent = readdir(dir);
	}
	head = tmp->next;
	closedir(dir);
	if (!head)
		head = new_node(strdup_upgrade(to_change));
	return (head);
}

void	wirldcard_expanding(char **line)
{
	int		i;
	char	**splt;
	char	*mark;

	if (!*line || !**line)
		return ;
	mark = ft_mark(*line);
	splt = upgrade_split(*line, mark);
	i = -1;
	while (splt[++i])
	{
		mark = mark_wildcard(splt[i]);
		if (mark && is_wildcard(mark))
			splt[i] = lst_to_str_wirld(expand_wildcard(splt[i], mark));
	}
	*line = arr_to_str(splt);
}

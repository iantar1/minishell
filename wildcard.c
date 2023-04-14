/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:01:01 by oidboufk          #+#    #+#             */
/*   Updated: 2023/04/14 00:39:19 by iantar           ###   ########.fr       */
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

void print_lst(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (head)
	{
		printf("otman:%s\n", head->content);
		head = head->next;
	}
	printf("DONE\n\n");
	head = tmp;
}

t_list	*expand_wildcard(char *to_change, char *mask)
{
	t_list			*head;
	struct dirent	*dir_ent;
	t_list			*tmp;
	DIR				*dir;
	char	*strdup_;

	dir = opendir(".");
	dir_ent = readdir(dir);
	strdup_ = ft_strdup(".");
	//printf("strdup_:%p\n", strdup_);
	head = new_node(strdup_);
	tmp = head;
	while (dir_ent)
	{
		//printf("lline : %s to_change : %s\n", dir_ent->d_name, to_change);
		if (is_in_filter(to_change, dir_ent->d_name, mask, 0))
		{
			head->next = new_node(ft_strdup(dir_ent->d_name));
			head = head->next;
		}
		dir_ent = readdir(dir);
	}
	head = tmp->next;
	free_it_(((char **)(&tmp->content)), 0);
	free(tmp);
	closedir(dir);
	if (!head)
		head = new_node(ft_strdup(to_change));
	//printf("SIZE:%d\n", ft_lstsize(head));
	//print_lst(head);
	return (head);
}

char	*mark_wildcard(char *str)
{
	int		i;
	int		flag;
	char	*mark;

	i = 0;
	flag = 0;
	if (!str)
		return (NULL);
	mark = malloc(ft_strlen(str) * sizeof(char));
	while (str[i])
	{
		ft_flag(str[i], &flag);
		if (str[i] == '*' && !flag)
			mark[i] = '9';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

int	is_wildcard(char *mark)
{
	int	i;

	i = 0;
	if (!mark)
		return (0);
	while (mark[i])
	{
		if (mark[i] == '9')
			return (1);
		i++;
	}
	return (0);
}

char	*lst_to_str(t_list *lst)
{
	int		i;
	char	*str;
	char	*tmp_str;
	t_list	*tmp;

	i = 0;
	if (!lst)
		return (NULL);
	tmp = lst;
	str = tmp->content;
	tmp = tmp->next;
	while (tmp)
	{
		if (!(tmp->content))
			return (str);
		tmp_str = str;
		str = ft_strjoin(str, " ");
		free(tmp_str);
		tmp_str = str;
		str = ft_strjoin(str, tmp->content);
		free(tmp_str);
		tmp = tmp->next;
	}
	return (str);
}

char	*arr_to_str(char **splt)
{
	int		i;
	char	*str;
	char	*tmp_str;

	if (!splt || !*splt)
		return (NULL);
	i = 0;
	str = splt[i];
	while (splt[++i])
	{
		tmp_str = str;
		str = ft_strjoin(str, " ");
		free(tmp_str);
		tmp_str = str;
		str = ft_strjoin(str, splt[i]);
		free(tmp_str);
	}
	remove_surrounded_sp(&str);
	return (str);
}

void	wirldcard_expanding(char **line)
{
	int		i;
	char	**splt;
	char	*mark;

	if (!*line || !**line)
		return ;
	splt = ft_split(*line, ' ');
	i = -1;
	while (splt[++i])
	{
		mark = mark_wildcard(splt[i]);
		if (mark && is_wildcard(mark))
			splt[i] = lst_to_str(expand_wildcard(splt[i], mark));
		if (mark)
			free(mark);
	}
	*line = arr_to_str(splt);
}

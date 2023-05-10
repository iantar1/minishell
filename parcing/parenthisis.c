/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthisis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:26:02 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 18:08:06 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

// void	remove_surrounded_sp(char **str)
// {
// 	int		len;
// 	int		start;

// 	start = 0;
// 	if (!**str)
// 		return ;
// 	while (*(*str + start) <= SPACE && *(*str + start) >= 0)
// 		start++;
// 	len = ft_strlen(*str) - 1;
// 	if (start == len + 1)
// 	{
// 		*str = NULL;
// 		return ;
// 	}
// 	while (len && (*(*str + len) <= SPACE) && *(*str + start) >= 0)
// 		len--;
// 	*str = ft_substr(*str, start, len - start + 1);
// }

void	fill_mark1(char *mark, int *check, int i)
{
	if (!*check)
		mark[i] = '1';
	else
		mark[i] = '0';
	(*check)++;
}

void	fill_mark2(char *mark, int *check, int i)
{
	if (*check == 1)
		mark[i] = '1';
	else
		mark[i] = '0';
	(*check)--;
}

char	*mark_first_parenthisis(char *str)
{
	int		check;
	int		i;
	char	*mark;
	int		flag;

	mark = upgrade_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
	i = -1;
	check = 0;
	flag = 0;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (str[i] == '(' && !flag)
			fill_mark1(mark, &check, i);
		else if (str[i] == ')' && !flag)
			fill_mark2(mark, &check, i);
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
}

int	surrounded_parenthisis(char *mark)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(mark);
	while (i < len - 1)
	{
		if (mark[i] != '0')
			return (0);
		i++;
	}
	if (mark[0] == '1' && mark[len - 1] == '1')
		return (1);
	return (0);
}

int	get_child_level(char **str)
{
	int		child_level;
	char	*mark;
	char	*tmp;
	char	**splt;

	mark = mark_first_parenthisis(*str);
	child_level = 0;
	while (surrounded_parenthisis(mark))
	{
		tmp = *str;
		splt = upgrade_split(*str, mark);
		*str = (free(tmp), splt[0]);
		if (*str)
			free(splt[1]);
		else
			return (free(splt), child_level);
		child_level = (free(splt), free(mark), child_level + 1);
		mark = mark_first_parenthisis(*str);
	}
	return (free(mark), child_level);
}

int	remove_first_parenthisis(char **str)
{
	int		child_level;
	char	*mark;
	char	*tmp;

	if (!*str)
		return (0);
	//tmp = *str;
	*str = strtrim_upgrade(*str, " 	");
	//free(tmp);
	child_level = get_child_level(str);
	tmp = *str;
	*str = strtrim_upgrade(*str, " 	");
	free(tmp);
	mark = mark_first_parenthisis(*str);
	if (surrounded_parenthisis(mark))
		return (remove_first_parenthisis(str), free(mark), child_level);
	return (free(mark), child_level);
}

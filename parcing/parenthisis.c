/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthisis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:26:02 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 16:03:58 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		*str = (splt[0]);
		if (!*str)
			return (child_level);
		child_level = (child_level + 1);
		mark = mark_first_parenthisis(*str);
	}
	return (child_level);
}

int	remove_first_parenthisis(char **str)
{
	int		child_level;
	char	*mark;
	char	*tmp;

	if (!*str)
		return (0);
	*str = strtrim_upgrade(*str, " 	");
	child_level = get_child_level(str);
	tmp = *str;
	*str = strtrim_upgrade(*str, " 	");
	mark = mark_first_parenthisis(*str);
	if (surrounded_parenthisis(mark))
		return (remove_first_parenthisis(str), child_level);
	return (child_level);
}

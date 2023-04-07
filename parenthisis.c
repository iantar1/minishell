/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthisis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:26:02 by iantar            #+#    #+#             */
/*   Updated: 2023/04/05 01:52:57 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_surrounded_sp(char **str)
{
	char	*tmp;
	int		len;
	int		start;

	start = 0;
	if (!**str)
		return ;
	while (*(*str + start) == SPACE)
		start++;
	len = ft_strlen(*str) - 1;
	if (start == len + 1)
	{
		*str = NULL;
		return ;
	}
	while ( len && *(*str + len) == SPACE)
		len--;
	tmp = *str;
	*str = ft_substr(*str, start, len - start + 1);
	free(tmp);
}

char	*mark_first_parenthisis(char *str)//to remove the first parenthesis.(ls | cat > out (cat out | wc)) -> ls | cat > out (cat out | wc)
{
	int		check;
	int		i;
	char	*mark;

	mark = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = -1;
	check = 0;
	while (str[++i])
	{
		if (str[i] == '(')
		{
			if (!check)
				mark[i] = '1';
			else
				mark[i] = '0';
			check++;
		}
		else if (str[i] == ')')
		{
			if (check == 1)
				mark[i] = '1';
			else
				mark[i] = '0';
			check--;
		}
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
//tomorrow remove the spaces from the border.
//than continue
int	remove_first_parenthisis(char **str)
{
	int		child_level;
	char	*mark;
	char	*tmp;
	char	**splt;

	remove_surrounded_sp(str);
	if (!*str)
		return (0);
	mark = mark_first_parenthisis(*str);
	child_level = 0;
	while (surrounded_parenthisis(mark))
	{
		tmp = *str;
		splt = upgrade_split(*str, mark);
		*str = splt[0];
		free(tmp);
		if (*str)
			free(splt[1]);
		else
			return (free(splt), child_level);
		free(splt);
		//printf("mark:%s", mark);
		child_level++;
		remove_surrounded_sp(str);
		printf("srtr:%s\n", *str);
		mark = mark_first_parenthisis(*str);
	}
	if (!child_level)
		free(mark);
	return (child_level);
}
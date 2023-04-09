/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amniguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:59:52 by iantar            #+#    #+#             */
/*   Updated: 2023/04/09 03:17:21 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//ls > "empty" or "more than one after expanding"
//if ther is quotes it's not an ambiguous redire
//export a=""hell 
//export a="x        y"
//ls > "" no such file or directory

int	just_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 34 || str[i] == 34)
	{
		if (!str[++i])
			return (1);
	}
	return (0);
}

int	check_ambiguous(char *str)
{
	char	**splt;
	int		check;

	check = 0;
	if (!str)
		return (0);
	str = ft_expand(str);//free()
	printf("str=%s\n", str);
	if (just_quote(str))
		check++;
	str = remove_quote(str);
	if (!*str && check)
		return (0);
	splt = ft_split(str, ' ');
	if (!splt[0] || len_ptr(splt) > 1)
		return (free_ptr(splt), 1);
	return (free_ptr(splt), 0);
}

int	amniguous_redirect(char	*str)
{
	char	*mark;
	char	**splt;
	int		i;

	i = 0;
	mark = mark_redirection(str, 1);
	if (!need_split(mark))
		return (0);
	splt = upgrade_split(str, mark);
	while (splt[i])
	{
		if (!ft_strcmp(splt[i], "<") || !ft_strncmp(splt[i], ">", 1))
		{
			if (check_ambiguous(splt[i + 1]))
				return (free_ptr(splt), 1);
		}
		i++;
	}
	return (free_ptr(splt), 0);
}

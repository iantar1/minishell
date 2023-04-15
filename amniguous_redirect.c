/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amniguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:59:52 by iantar            #+#    #+#             */
/*   Updated: 2023/04/15 10:02:55 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	just_quote(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] == 34 || str[i] == 39)
// 	{
// 		if (!str[++i])
// 			return (1);
// 	}
// 	return (0);
// }

int	inside_quotes(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (str[i] == '$' && !flag)
			return (0);
	}
	return (1);
}

int	check_ambiguous(char *str)
{
	char	**splt;
	int		check;

	check = 0;
	if (!str)
		return (0);
	if (inside_quotes(str))
		return (0);
	str = ft_expand(str);//free()
	str = remove_quote(str);
	splt = ft_split(str, ' ');
	if (!splt[0] || len_ptr(splt) > 1)
		return (free_ptr(splt), 1);
	return (free_ptr(splt), 0);
}

int	check_ambiguous_wirldcar(char *str)
{
	char	*mark;

	mark = mark_wildcard(str);
	if (is_wildcard(mark))
	{
		if (ft_lstsize(expand_wildcard(str, mark)))
			return (free(mark), 1);
	}
	return (free(mark), 0);
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
			if (check_ambiguous_wirldcar(splt[i + 1]))
				return (free_ptr(splt), 1);
		}
		i++;
	}
	return (free_ptr(splt), 0);
}

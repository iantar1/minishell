/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:59:52 by iantar            #+#    #+#             */
/*   Updated: 2023/05/12 16:16:52 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*mark_for_ambiguis(char *str)
{
	char	*mark;
	int		i;
	int		flag;

	flag = 0;
	i = -1;
	mark = upgrade_malloc((ft_strlen(str) + 1) * sizeof(char), 0);
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (str[i] <= 32 && str[i] > 0 && !flag)
			mark[i] = '1';
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
}

int	check_ambiguous(char *str)
{
	char	**splt;
	int		check;
	char	*tmp;
	char	*mark;

	check = 0;
	if (!str)
		return (0);
	if (inside_quotes(str))
		return (0);
	str = ft_expand(str);
	str = remove_quote(str);
	unreform_quote(str);
	tmp = str;
	if (!str || !*str)
		return (1);
	mark = mark_for_ambiguis(str);
	splt = upgrade_split(str, mark);
	if (!splt[0] || len_ptr(splt) > 1)
		return (1);
	return (0);
}

int	check_ambiguous_wirldcar(char *str)
{
	char	*mark;

	mark = mark_wildcard(str);
	if (is_wildcard(mark))
	{
		if (ft_lstsize(expand_wildcard(str, mark)))
			return (1);
	}
	return (0);
}

int	ambiguous_redirect(char	*str)
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
				return (1);
			if (check_ambiguous_wirldcar(splt[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

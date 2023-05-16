/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:55:57 by iantar            #+#    #+#             */
/*   Updated: 2023/05/15 09:34:30 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*space_join(char **splt)
{
	char	*rtn_str;
	char	*tmp;
	int		i;

	if (!splt || !*splt)
		return (NULL);
	i = 0;
	if (splt[i + 1])
		rtn_str = strjoin_upgrade(splt[i], " ");
	else
		rtn_str = strjoin_upgrade(splt[i], "");
	tmp = rtn_str;
	while (splt[++i])
	{
		rtn_str = strjoin_upgrade(rtn_str, splt[i]);
		if (splt[i + 1])
		{
			tmp = rtn_str;
			rtn_str = strjoin_upgrade(rtn_str, " ");
		}
		tmp = rtn_str;
	}
	return (rtn_str);
}

int	get_index_out(char **splt, char *red, int len)
{
	int	index;

	index = -1;
	if (!len)
	{
		while (splt[++index])
			if (!ft_strncmp(splt[index], red, 1))
				return (index);
	}
	else
	{
		while (--len)
			if (!ft_strncmp(splt[len], red, 1))
				return (len);
	}
	return (0);
}

int	get_index_in(char **splt, char *red, int len)
{
	int	index;

	index = -1;
	if (!len)
	{
		while (splt[++index])
			if (!ft_strncmp(splt[index], red, 1))
				return (index);
	}
	else
	{
		while (--len)
			if (!ft_strncmp(splt[len], red, 1))
				return (len);
	}
	return (0);
}

void	swap_red(char **splt, int in_out)
{
	char	index1;
	char	index2;

	if (in_out == OUT)
	{
		index1 = get_index_out(splt, ">", 0);
		index2 = get_index_out(splt, ">", len_ptr(splt));
	}
	else
	{
		index1 = get_index_in(splt, "<", 0);
		index2 = get_index_in(splt, "<", len_ptr(splt));
	}
	ft_swap(splt + index1, splt + index2);
	ft_swap(splt + ++index1, splt + ++index2);
}

char	*check_swap_red(char *line)
{
	char	*mark;
	char	**splt;
	char	*rtn_str;

	if (!line)
		return (NULL);
	mark = mark_redirection(line, SPACE);
	splt = upgrade_split(line, mark);
	if (count_red(splt, ">") + count_red(splt, ">>") > 1)
		swap_red(splt, OUT);
	if (count_red(splt, "<") + count_red(splt, "<<") > 1)
		swap_red(splt, IN);
	rtn_str = space_join(splt);
	return (rtn_str);
}

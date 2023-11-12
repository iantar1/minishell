/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_join_fun.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:23:19 by iantar            #+#    #+#             */
/*   Updated: 2023/11/10 21:55:17 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*_join_evrything_(char **splt, int len_splt)
{
	char	*rtn_str;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = -1;
	while (splt[++i] || i < len_splt)
	{
		j = -1;
		while (splt[i] && splt[i][++j])
			len++;
	}
	rtn_str = upgrade_malloc(len + 1, 0);
	len = -1;
	i = 0;
	while (splt[i] || i < len_splt)
	{
		j = -1;
		while (splt[i] && splt[i][++j])
			rtn_str[++len] = splt[i][j];
		i++;
	}
	rtn_str[++len] = '\0';
	return (rtn_str);
}

char	*join_with_sp_norm(char *rtn_str, char **splt)
{
	int		i;

	i = 0;
	while (splt && splt[++i])
	{
		rtn_str = strjoin_upgrade(rtn_str, splt[i]);
		if (splt[i + 1])
			rtn_str = strjoin_upgrade(rtn_str, " ");
	}
	return (rtn_str);
}

char	*join_with_sp(char *str)
{
	char	**splt;
	char	*rtn_str;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	splt = ft_split(str, SPACE);
	if (!splt || !*splt)
		return (NULL);
	if (splt[i + 1])
		rtn_str = strjoin_upgrade(splt[i], " ");
	else
		rtn_str = strjoin_upgrade(splt[i], "");
	rtn_str = join_with_sp_norm(rtn_str, splt);
	return (rtn_str);
}

char	*join_evrything(char **splt)
{
	char	*rtn_str;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = -1;
	while (splt[++i])
	{
		j = -1;
		while (splt[i] && splt[i][++j])
			len++;
	}
	rtn_str = upgrade_malloc(len + 1, 0);
	len = -1;
	i = 0;
	while (splt[i])
	{
		j = -1;
		while (splt[i] && splt[i][++j])
			rtn_str[++len] = splt[i][j];
		i++;
	}
	rtn_str[++len] = '\0';
	return (rtn_str);
}

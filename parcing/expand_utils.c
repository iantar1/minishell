/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:19:12 by iantar            #+#    #+#             */
/*   Updated: 2023/11/10 21:54:38 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_mark(char *str)
{
	int				i;
	unsigned char	check[2];
	char			*mark;

	if (!str)
		return (NULL);
	i = -1;
	mark = upgrade_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
	ft_bzero(check, 2);
	while (str[++i])
	{
		if (str[i] == 34 && !(check[1] % 2))
			check[0]++;
		if (str[i] == 39 && !(check[0] % 2))
			check[1]++;
		if (check[0] % 2 || (!(check[1] % 2) && str[i] == 34))
			mark[i] = '0';
		else if (!(check[0] % 2) && !(check[1] % 2)
			&& str[i] != 34 && str[i] != 39)
			mark[i] = '3';
		else
			mark[i] = '2';
	}
	mark[i] = '\0';
	return (mark);
}

int	need_expand(char *str)
{
	int	i;
	int	check1;
	int	check2;

	i = -1;
	check1 = 0;
	check2 = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == 34)
			check1++;
		else if (str[i] == 39 && !(check1 % 2))
			check2++;
		else if ((str[i] == '$' && ((check1 % 2 && !(check2 % 2))
					|| (!(check1 % 2)
						&& !(check2 % 2)))) && (str[i + 1] == '?'
				|| str[i + 1] == '_' || ft_isalnum(str[i + 1])))
			return (1);
	}
	return (0);
}

int	len_to_exp(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '?')
		return (2);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char	*get_value(char *key, int len)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var_name, key, len)
			&& (int)ft_strlen(tmp->var_name) == len)
			return (strdup_upgrade(tmp->line));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*reform_quotes(char *str)
{
	int		i;

	if (!str || !*str)
		return (str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34)
			str[i] = DOUBLE_QUOTE;
		if (str[i] == 39)
			str[i] = SINGLE_QUOTE;
	}
	return (str);
}

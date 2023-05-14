/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:13:04 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/13 11:05:14 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

char	*delete_indexs(char *str, int index[2], int *j)
{
	int		i;
	int		y;
	char	*new;

	i = 0;
	y = 0;
	new = malloc((oi_strlen(str) + 1) * sizeof(char));
	while (str[i])
	{
		if (i != index[0] && i != index[1])
			new[y++] = str[i];
		i++;
	}
	new[y] = '\0';
	*j -= 2;
	return (new);
}

char	*parse_value(char *val)
{
	int		i;
	char	sym;
	int		index[2];
	int		sym_count;
	char	*tmp;

	i = -1;
	sym = symbole(val);
	sym_count = 0;
	while (val && val[++i])
	{
		if (val[i] == sym && sym)
		{
			sym_count++;
			index[sym_count - 1] = i;
		}
		if (sym_count == 2)
		{
			tmp = delete_indexs(val, index, &i);
			val = (free(val), oi_strdup(tmp));
			sym_count = 0;
			sym = (free(tmp), symbole(val));
		}
	}
	return (val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:37:49 by iantar            #+#    #+#             */
/*   Updated: 2023/11/10 21:47:46 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*unreform_quote(char *str)
{
	int		i;

	if (!str || !*str)
		return (str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == DOUBLE_QUOTE)
			str[i] = 34;
		if (str[i] == SINGLE_QUOTE)
			str[i] = 39;
	}
	return (str);
}

char	*ft_change_part_norm(t_vars var, char *value, int *i)
{
	int		new_len;
	int		len_value;
	int		j;
	char	*rtn_str;

	j = -1;
	rtn_str = NULL;
	if (!value)
		len_value = 0;
	else
		len_value = ft_strlen(value);
	new_len = ft_strlen(var.str) - (var.end - var.start) + len_value;
	rtn_str = upgrade_malloc(new_len + 1, 0);
	while (++(*i) < var.start)
		rtn_str[*i] = var.str[*i];
	while (++j < len_value)
		rtn_str[(*i)++] = value[j];
	return (rtn_str);
}

char	*ft_change_part(t_vars var, char *value, int *curser)
{
	int		new_len;
	int		i;
	int		j;
	char	*rtn_str;

	i = -1;
	rtn_str = ft_change_part_norm(var, value, &i);
	*curser = i - 1;
	j = 0;
	while (var.str[var.end + ++j])
		rtn_str[i++] = var.str[var.end + j];
	rtn_str[i] = '\0';
	if (!inside_quotes(var.str))
	{
		new_len = ft_strlen(rtn_str);
		rtn_str = join_with_sp(rtn_str);
		*curser = *curser - (new_len - ft_strlen(rtn_str));
	}
	return (rtn_str);
}

void	ft_expand_norm(t_vars var, char **splt)
{
	char	*value;

	while (splt[var.i] && splt[var.i][(++var.j)])
	{
		if (splt[var.i][var.j] == '$')
		{
			if (!splt[var.i][var.j + 1])
				break ;
			if ((!ft_isalnum(splt[var.i][var.j + 1])
				&& splt[var.i][var.j + 1] != '_')
				&& splt[var.i][var.j + 1] != '?' && ++var.j)
				continue ;
			var.start = var.j;
			var.end = len_to_exp(&splt[var.i][var.j]) + var.start - 1;
			var.str = splt[var.i];
			value = reform_quotes(get_value(&splt[var.i][var.j + 1],
						var.end - var.start));
			splt[var.i] = ft_change_part(var, value, &(var.j));
		}
	}
}

char	*ft_expand(char *str)
{
	char	**splt;
	char	*mark;
	t_vars	var;
	int		len_splt;

	var.i = -1;
	if (!str)
		return (NULL);
	mark = expand_mark(str);
	splt = upgrade_split(str, mark);
	len_splt = len_ptr(splt);
	while (splt && (splt[++(var.i)] || var.i < len_splt))
	{
		if (need_expand(splt[var.i]))
		{
			var.j = -1;
			ft_expand_norm(var, splt);
		}
	}
	if (!splt)
		return (NULL);
	mark = _join_evrything_(splt, len_splt);
	return (mark);
}

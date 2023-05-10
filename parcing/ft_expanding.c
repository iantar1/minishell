/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:37:49 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 20:14:18 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_mark(char *str)//done
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

int	need_expand(char *str)//done
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
		else if ((str[i] == '$' && ((check1 % 2 && !(check2 % 2)) || (!(check1 % 2)
						&& !(check2 % 2)))) && (str[i + 1] == '?'
				|| str[i + 1] == '_' || ft_isalnum(str[i + 1])))
			return (1);
	}
	return (0);
}

char	*exp_from_env(char *key)//done
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = g_env;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->var_name, ft_strlen(key)))
			return (tmp->line);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*_join_evrything_(char **splt, int len_splt)//done
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

int	len_to_exp(char *str)//done
{
	int	i;

	i = 1;
	if (str[i] == '?')
		return (2);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char	*get_value(char *key, int len)//done
{
	int		i;
	t_env	*tmp;

	i = 0;
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

char	*join_with_sp_norm(char *rtn_str, char **splt)//done
{
	int		i;
	char	*tmp;

	i = 0;
	while (splt && splt[++i])
	{
		tmp = rtn_str;
		rtn_str = strjoin_upgrade(rtn_str, splt[i]);
		free(tmp);
		if (splt[i + 1])
		{
			tmp = rtn_str;
			rtn_str = strjoin_upgrade(rtn_str, " ");
			free(tmp);
		}
	}
	return (rtn_str);
}

char	*join_with_sp(char *str)//done
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
	return (free_ptr(splt), rtn_str);
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
	char	*tmp;

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
		tmp = rtn_str;
		rtn_str = join_with_sp(rtn_str);
		free(tmp);
		*curser = *curser - (new_len - ft_strlen(rtn_str));
	}
	return (rtn_str);
}

void	ft_expand_norm(t_vars var, char **splt)///////////*************
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
			value = get_value(&splt[var.i][var.j + 1], var.end - var.start);
			splt[var.i] = ft_change_part(var, value, &(var.j));
			free(value);
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
	free(mark);
	if (!splt)
		return (NULL);
	mark = _join_evrything_(splt, len_splt);
	free_ptr(splt);
	return (mark);
}

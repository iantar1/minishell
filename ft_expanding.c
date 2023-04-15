/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:37:49 by iantar            #+#    #+#             */
/*   Updated: 2023/04/15 01:14:30 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_mark(char *str)
{
	int		i;
	int		check[2];
	char	*mark;

	mark = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = -1;
	check[0] = 0;
	check[1] = 0;
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
		if (str[i] == 39 && !(check1 % 2))
			check2++;
		if ((str[i] == '$' && ((check1 % 2 && !(check2 % 2)) || (!(check1 % 2)
						&& !(check2 % 2)))) && (str[i + 1] == '?'
				|| str[i + 1] == '_' || ft_isalnum(str[i + 1])))
			return (1);
	}
	return (0);
}

char	*exp_from_env(char *key)
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

void	double_free(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
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
		while (splt[i][++j])
			len++;
	}
	rtn_str = malloc(len + 1);
	len = -1;
	i = -1;
	while (splt[++i])
	{
		j = -1;
		while (splt[i][++j])
			rtn_str[++len] = splt[i][j];
	}
	rtn_str[++len] = (double_free(splt), '\0');
	return (rtn_str);
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
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = g_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var_name, key, len)
			&& (int)ft_strlen(tmp->var_name) == len)
			return (tmp->line);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*join_with_sp(char *str)
{
	char	**splt;
	char	*rtn_str;
	char	*tmp;
	int		i;

	i = 0;
	if (!str)
		return(NULL);
	splt = ft_split(str, ' ');
	if (!splt || !*splt)
		return (NULL);
	if (splt[i + 1])
		rtn_str = ft_strjoin(splt[i], " ");
	else
		rtn_str = ft_strjoin(splt[i], "");
	tmp = rtn_str;
	while (splt && splt[++i])
	{
		rtn_str = ft_strjoin(rtn_str, splt[i]);
		if (splt[i + 1])
			rtn_str = ft_strjoin(rtn_str, " ");
		tmp = rtn_str;
		i++;
	}
	//printf("****rtn_str%d:%s\n", i, rtn_str);
	return (rtn_str);
}
//HERE AM3ALLAM

char	*ft_change_part(t_vars var, char *value, int *curser)
{
	int		new_len;
	int		len_value;
	int		i;
	int		j;
	char	*rtn_str;

	i = -1;
	j = -1;
	rtn_str = NULL;
	if (!value)
		len_value = 0;
	else
		len_value = ft_strlen(value);
	new_len = ft_strlen(var.str) - (var.end - var.start) + len_value;
	rtn_str = malloc(new_len + 1);
	while (++i < var.start)
		rtn_str[i] = var.str[i];
	while (++j < len_value)
		rtn_str[i++] = value[j];
	*curser = i - 1;
	j = 0;
	while (var.str[var.end + ++j])
		rtn_str[i++] = var.str[var.end + j];
	rtn_str[i] = '\0';
	if (!inside_quotes(var.str))
		rtn_str = join_with_sp(rtn_str);//free
	//free(var.str);
	return (rtn_str);
}

void	ft_expand_norm(t_vars var, char **splt)
{
	while (splt[var.i][++(var.j)])
	{
		if (splt[var.i][var.j] == '$')
		{
			if ((!ft_isalnum(splt[var.i][var.j + 1])
				&& splt[var.i][var.j + 1] != '_')
				&& splt[var.i][var.j + 1] != '?' && ++var.j)
				continue ;
			var.start = var.j;
			var.end = len_to_exp(&splt[var.i][var.j]) + var.start - 1;
			var.str = splt[var.i];
			splt[var.i] = ft_change_part(var, get_value(&splt[var.i]
					[var.j + 1], var.end - var.start), &(var.j));
		}
		//printf("splt[var.i]=%s\n", splt[var.i]);
	}
}

char	*ft_expand(char *str)
{
	char	**splt;
	t_vars	var;

	var.i = -1;
	if (!str)
		return (NULL);
	splt = upgrade_split(str, expand_mark(str));
	while (splt[++(var.i)])
	{
		if (need_expand(splt[var.i]))
		{
			var.j = -1;
			ft_expand_norm(var, splt);
		}
	}
	if (!splt || !splt[0])
		return (NULL);
	return (join_evrything(splt));
}

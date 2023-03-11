/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:37:49 by iantar            #+#    #+#             */
/*   Updated: 2023/03/07 11:53:34 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//$?$?"$|$$$%
//void	

char	*expand_mark(char *str)
{
	int		i;
	int		check[2];
	char	*mark;

	i = 0;
	if (!str || !*str)
		return (NULL);
	mark = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!mark)
		return (NULL);
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
		if ((str[i] == '$' && ((check1 % 2 || check2 % 2) || (!(check1 % 2)
						&& !(check2 % 2)))) && (str[i + 1] == '?' || (str[i + 1]
					>= 65 && str[i + 1] <= 90)
				|| (str[i + 1] >= 97 && str[i + 1] <= 122)))
			return (1);
	}
	return (0);
}

char	*exp_from_env(char *key, t_env *head_env, char exit_status)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = head_env;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->var_name, ft_strlen(key)))
			return (tmp->line);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_expand(char *str, t_env *head_env)
{
	char	**splt;
	int		i;

	i = 0;
	splt = upgrade_split(str, expand_mark(str));
	while (splt[i])
	{
		if (need_expand(splt[i]))
		{
			 
		}
	}
}

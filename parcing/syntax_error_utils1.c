/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:14:00 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 16:07:58 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	invalide_char(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (!flag && str[i] == ';')
			return (1);
	}
	return (0);
}

char	is_redi(char c)
{
	return (c == '>' || c == '<');
}

char	is_operator(char c)
{
	return (c == '|' || c == '&');
}

int	emty_parenthesis(char *str)
{
	int	i;
	int	check;
	int	rtn;
	int	flag;

	check = 0;
	rtn = 1;
	i = -1;
	flag = 0;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (check && (str[i] > 32 || str[i] < 0) && str[i] != ')' && !flag)
			rtn = 0;
		if (str[i] == '(' && !flag)
			rtn = (check++, 1);
		if (str[i] == ')' && !flag)
		{
			if (rtn)
				return (1);
			check--;
		}
	}
	return (0);
}

char	*remove_spaces(char *str)
{
	int		i;
	int		j;
	char	*rtn;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] > 32 || str[i] < 0)
			j++;
	rtn = upgrade_malloc(j + 1, 0);
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] > 32 || str[i] < 0)
			rtn[++j] = str[i];
	rtn[++j] = '\0';
	return (rtn);
}

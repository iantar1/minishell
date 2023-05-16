/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:14:00 by iantar            #+#    #+#             */
/*   Updated: 2023/05/15 13:44:25 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	unclosed_parenthesis(char *str)
{
	int		i;
	int		check;
	int		flag;

	i = -1;
	check = 0;
	flag = 0;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (str[i] == '(' && check >= 0 && !flag)
			check++;
		if (str[i] == ')' && !flag)
			check--;
	}
	return (check);
}

int	invalid_oper1(char *str)
{
	int		i;
	char	*_s;
	int		flag;

	i = -1;
	_s = remove_spaces(str);
	flag = 0;
	while (_s[++i])
	{
		ft_flag(_s[i], &flag);
		if (_s[i] == '|' && !flag)
		{
			if (_s[i + 1] == '&' || _s[i + 1] == ')')
				return (1);
		}
		else if (_s[i] == '&' && !flag)
		{
			if (_s[i + 1] == '|' || _s[i + 1] == ')')
				return (1);
		}
	}
	return (0);
}

int	invalid_oper3(char *str)
{
	int		i;
	char	*_s;
	int		flag;
	int		opr;

	_s = remove_spaces(str);
	opr = 0;
	i = -1;
	flag = 0;
	if (is_operator(_s[0]))
		return (1);
	while (_s[++i])
	{
		ft_flag(_s[i], &flag);
		if (opr > 2)
			return (1);
		if (is_operator(_s[i]) && !flag)
			opr++;
		else
			opr = 0;
	}
	if (is_operator(_s[--i]))
		return (1);
	return (0);
}

int	invalid_oper2(char *str)
{
	int				i;
	int				flag;
	unsigned char	var[2];

	i = -1;
	flag = 0;
	ft_bzero(var, 2);
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		if (str[i] <= 32 && str[i] > 0)
			var[0] = 1;
		else if (is_operator(str[i]) && !flag)
		{
			if ((var[0] && var[1]) || var[1] > 2)
				return (1);
			(var[1])++;
			var[0] = 0;
		}
		else
			ft_bzero(var, 2);
	}
	return (0);
}

int	invalid_red1(char *str)
{
	int		i;
	char	*_s;
	int		flag;
	int		opr;

	_s = remove_spaces(str);
	opr = 0;
	i = -1;
	flag = 0;
	while (_s[++i])
	{
		ft_flag(_s[i], &flag);
		if (opr > 2)
			return (1);
		else if (is_redi(_s[i]) && !flag)
			opr++;
		else
			opr = 0;
	}
	if (is_redi(_s[--i]))
		return (1);
	return (0);
}

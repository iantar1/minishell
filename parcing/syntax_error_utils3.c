/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:14:00 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 16:13:48 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	invalid_red2(char *str)
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
		if (_s[i] == '>' && !flag)
		{
			if (_s[i + 1] == '<')
				return (1);
		}
		else if (_s[i] == '<' && !flag)
		{
			if (_s[i + 1] == '>')
				return (1);
		}
	}
	return (0);
}

int	invalid_red3(char *str)
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
		else if (is_redi(str[i]) && !flag)
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

char	unvalid_next_open_parth(char *str)
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
		if (!is_operator(_s[i]) && _s[i] != '(' && _s[i + 1] == '(' && !flag)
			return (1);
		if (_s[i] == '(' && !flag)
		{
			if (is_operator(_s[i + 1]))
				return (1);
		}
	}
	return (0);
}

int	invalid_next_red(char *str)
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
		if (is_redi(_s[i]) && !flag)
		{
			if (is_operator(_s[i + 1]) || _s[i + 1] == '(')
				return (1);
		}
	}
	return (0);
}

char	unvalid_next_close_parth(char *str)
{
	int		i;
	int		flag;
	char	*s_;

	s_ = remove_spaces(str);
	i = -1;
	flag = 0;
	while (s_[++i])
	{
		ft_flag(s_[i], &flag);
		if (s_[i] == ')' && !flag)
		{
			if (s_[i + 1] && s_[i + 1] != ')'
				&& (!is_operator(s_[i + 1]) && !is_redi(s_[i + 1])))
				return (1);
		}
	}
	return (0);
}

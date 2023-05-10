/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:14:00 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 18:08:17 by oidboufk         ###   ########.fr       */
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

	check = 0;
	rtn = 1;
	i = -1;
	while (str[++i])
	{
		if (check && str[i] > 32 && str[i] != ')')
			rtn = 0;
		if (str[i] == '(')
			rtn = (check++, 1);
		if (str[i] == ')')
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

//this will handle  &| 
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
				return (free(_s), 1);
		}
		else if (_s[i] == '&' && !flag)
		{
			if (_s[i + 1] == '|' || _s[i + 1] == ')')
				return (free(_s), 1);
		}
	}
	return (free(_s), 0);
}


//a cmd start or end with | or &, and  |||.. &&&...
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
		return (free(_s), 1);
	while (_s[++i])
	{
		if (opr > 2)
			return (free(_s), 1);
		if (is_operator(_s[i]) && !flag)
			opr++;
		else
			opr = 0;
	}
	if (is_operator(_s[--i]))
		return (free(_s), 1);
	return (free(_s), 0);
}

//this will handle space between oper
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

//>>> <<<
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
		if (opr > 2)
			return (free(_s), 1);
		else if (is_redi(_s[i]) && !flag)
			opr++;
		else
			opr = 0;
	}
	if (is_redi(_s[--i]))
		return (free(_s), 1);
	return (free(_s), 0);
}
//>< <>
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
				return (free(_s), 1);
		}
		else if (_s[i] == '<' && !flag)
		{
			if (_s[i + 1] == '>')
				return (free(_s), 1);
		}
	}
	return (free(_s), 0);
}

//two red between sp
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

/*
*/

//this will check (| (& 
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
			return (free(_s), 1);
		if (_s[i] == '(' && !flag)
		{
			if (is_operator(_s[i + 1]))
				return (free(_s), 1);
		}
	}
	return (free(_s), 0);
}
/*
*/

//> | > (
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
				return (free(_s), 1);
		}
	}
	return (free(_s), 0);
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
				return (free(s_), 1);
		}
	}
	return (free(s_), 0);
}

int	surnd_parnt(char *str)
{
	char	*mark;
	char	*tmp;

	tmp = strtrim_upgrade(str, "	 ");
	mark = mark_first_parenthisis(tmp);
	free(tmp);
	if (surrounded_parenthisis(mark))
		return (free(mark), 1);
	return (free(mark), 0);
}

int	check_syntax(char *str)
{
	if (emty_parenthesis(str)
		|| unclosed_parenthesis(str) || unclosed_quote(str))
		return (1);
	if (invalid_oper1(str))
		return (/*printf("invalid_oper1\n"), */1);
	if (invalid_oper2(str))
		return (/*printf("invalid_oper2\n"), */1);
	if (invalid_oper3(str))
		return (/*printf("invalid_oper3\n"), */1);
	if (unvalid_next_close_parth(str))
		return (/*printf("next_close_parth\n"), */1);
	if (invalid_red1(str))
		return (/*printf("invalid_red1\n"), */1);
	if (invalid_red2(str))
		return (/*printf("invalid_red2\n"), */1);
	if (invalid_red3(str))
		return (/*printf("invalid_red3\n"), */1);
	if (invalid_next_red(str))
		return (/*printf("invalid_next_red\n"), */1);
	if (unvalid_next_open_parth(str))
		return (/*printf("unvalid_next_open_parth\n"), */1);
	if (invalide_char(str))
		return (1);
	return (0);
}

int	recur_check(char *(*marker)(char *, int), char(*is_red_opr)(char), char *str)
{
	char	*mark;
	int		i;
	char	**splt;

	mark = marker(str, 0);
	splt = upgrade_split(str, mark);
	i = -1;
	if (need_split(mark))
	{
		while (splt[++i])
		{
			if (!is_red_opr(splt[i][0]))
			{
				if (syntax_error(splt[i]))
					return (free(mark), free_ptr(splt), 1);
			}
		}
	}
	return (free(mark), free_ptr(splt), 0);
}

int	syntax_error(char *str)//ft_strdup(str);
{
	char	*tmp;

	if (check_syntax(str))
		return (1);
	while (surnd_parnt(str))
		remove_first_parenthisis(&str);
	//system("leaks minishell");
	if (recur_check(ft_mark_operator, is_operator, str))
		return (free(str), 1);
	tmp = str;
	str = reform_redirection(str);
	//free(tmp);
	if (recur_check(mark_redirection, is_redi, str))
		return (free(str), 1);
	return (free(str), 0);
}


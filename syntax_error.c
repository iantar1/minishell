/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:14:00 by iantar            #+#    #+#             */
/*   Updated: 2023/03/31 01:15:39 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"

char	closed_parenthesis(char *str)
{
	int		i;
	int		check;
	char	first;

	i = -1;
	check = 0;
	first = 0;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '(' && check >= 0)
			check++;
		if (str[i] == ')')
			check--;
	}
	if (!check)
		return (1);
	return (0);
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
		if (check && ft_isprint(str[i]) && str[i] != ')')
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
//(()) dosn't show syntax error , just exit status = 1
int	double_parenthesis(char *str)
{
	int	i;
	int	check;

	i = -1;
	while (str[i])
	{
		if (str[i] == ')')
			check = 1;
	}
}
//if you enter |||.. or &&&... 
int	valid_operators(char *mark)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (mark[i])
	{
		while (mark[i++] == '2')
			len++;
		if (len > 2)
			return (0);
		else
			len = 0;
	}
	return (1);
}

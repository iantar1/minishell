/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:14:00 by iantar            #+#    #+#             */
/*   Updated: 2023/04/10 11:40:11 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	unclosed_parenthesis(char *str)
{
	int		i;
	int		check;
	char	first;
	char	flag;

	i = -1;
	check = 0;
	first = 0;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == 34 && flag != 39)
		{
			if (!flag)
				flag = 34;
			else
				flag = 0;
		}
		if (str[i] == 39 && flag != 34)
		{
			if (!flag)
				flag = 34;
			else
				flag = 0;
		}
		if (str[i] == '(' && check >= 0 && !flag)
			check++;
		if (str[i] == ')' && !flag)
			check--;
	}
	return (check);
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

//if you enter |||.. or &&&... |>
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

char	*mark_and_or(char *str)
{
	int		i;
	char	*mark;
	char	check;

	mark = malloc(sizeof(char) * ft_strlen(str) + 1);
	check = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 && check != 39)
		{
			if (check)
				check = 0;
			else
				check = 34;
		}
		if (str[i] == 39 && check != 34)
		{
			if (check)
				check = 0;
			else
				check = 39;
		}
		if ((str[i] == '|' || str[i] == '&') && !check)
			mark[i] = '0';
		else if ((str[i] == '>' || str[i] == '<') && !check)
			mark[i] = '2';
		else if (!check && str[i] == ';')
			mark[i] = '3';
		else
			mark[i] = '1';
	}
	mark[i] = '\0';
	return (mark);
}

char	*mark_syn_err(char *str)
{
	int		i;
	int		check;
	char 	*mark;

	mark = malloc(ft_strlen(str) * sizeof(char));
	check = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 && check != 39)
		{
			if (check)
				check = 0;
			else
				check = 34;
		}
		if (str[i] == 39 && check != 34)
		{
			if (check)
				check = 0;
			else
				check = 39;
		}
		if ((str[i] == '|' || str[i] == '&') && !check)
			mark[i] = '4';
		else if ((str[i] == '>' || str[i] == '<') && !check)
			mark[i] = '2';
		else if (!check && (str[i] == '(' || str[i] == ')'))
			mark[i] = '3';
		else if (str[i] == ' ')
			mark[i] = '1';
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
}

char	is_operator(char c)
{
	return (c == '|' || c == '&'  || c == '>' || c == '<');
}

char	unvalid_next_parenthesis(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ')' && str[i + 1] && str[i + 1] != ')' && !is_operator(str[i + 1]))
			return (1);
		if (str[i] != '(' && str[i + 1] && str[i + 1] == '(')
			return (1);  
	}
	return (0);
}


// char	*ft_reform_rediration(char *str)
// {
// 	int		i;
// 	char	*mark;

// 	mark = ft_mark_operator(str);
	
// }

int	check_syntax_error(char *str)
{
	char	*mark;
	char	**splt;
	int		i;
	//int		check;

	remove_first_parenthisis(&str);
	if (!str || !*str)
		return (0);
	if (str[0] == '|' || str[0] == '&')
		return (1);
	if (is_operator(str[ft_strlen(str) - 1]))
		return (1);
	mark = ft_mark_operator(str);
	splt = upgrade_split(str, mark);
	//&& || | 
	//check = 0;//just for frr3 lmemory
	if (need_split(mark))
	{
		i = -1;
		while (splt[++i])
		{
			printf("llllll\n");
			if (is_operator(splt[i][0]) && !splt[i + 1])
				return (1);
			if (splt[i][0] != '|' && splt[i][0] != '&')
				check_syntax_error(splt[i]);
		}
		//free_ptr(splt);
	}
	else
	{
		if (str)
		{
			printf("******\n");
			if (str[ft_strlen(str) - 1] != '>' && str[ft_strlen(str) - 1] != '>')
				str = reform_redirection(str);
			mark = mark_redirection(str, 1);// 1 for removing spaces
			splt = upgrade_split(str, mark);
			// >> << > <
			if (need_split(mark))
			{
				i = -1;
				while (splt[++i])
				{
					if (is_operator(splt[i][0]) && !splt[i + 1])
						return (1);
					if (splt[i + 1] && splt[i][0] == ')' && !is_operator(splt[i + 1][0]))
						return (1);
					if (splt[i + 1] && splt[i][0] != '(' && splt[i + 1][0] && splt[i + 1][0] == '(')
						return (1);
				}
			}
		}
	}
	return (0);
}

int	syntax_error(char *str)
{
	char	*mark;
	char	**splt;
	int		i;

	i = -1;
	if (!str || !*str)
		return (0);
	if (emty_parenthesis(str) || unclosed_parenthesis(str) || unclosed_quote(str))
		return (1);
	//while (splt) with || && than join 2D_arr
	mark = mark_and_or(str);
	splt = upgrade_split(str, mark);
	while (splt && splt[++i])
	{
		if (splt[i][0] == ';')
			return (1);
		if (ft_strlen(splt[i]) > 2 || (ft_strncmp(splt[i], "||", ft_strlen(splt[i]))
			&& ft_strcmp(splt[i], "&&") && ft_strncmp(splt[i], ">>", ft_strlen(splt[i])) && ft_strncmp(splt[i], "<<", ft_strlen(splt[i]))))
				return (1);
	}
	free_ptr(splt);
	if (check_syntax_error(str))
		return (1);
	return (0);
}
// || || ||
// 


//
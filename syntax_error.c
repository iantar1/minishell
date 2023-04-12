/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:14:00 by iantar            #+#    #+#             */
/*   Updated: 2023/04/12 07:33:26 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



//if you enter |||.. or &&&... |>
/*
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




char	unvalid_next_parenthesis(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] > 32)
			j++;
	tmp = malloc(j + 1);
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] > 32)
			tmp[++j] = str[i];
	tmp[++j] = '\0';
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == ')' && tmp[i + 1] && tmp[i + 1] != ')' && !is_operator(tmp[i + 1]))
			return (free(tmp), 1);
		if (tmp[i] != '(' && tmp[i + 1] && tmp[i + 1] == '(')
			return (free(tmp), 1);  
	}
	return (free(tmp), 0);
}


// char	*ft_reform_rediration(char *str)
// {
// 	int		i;
// 	char	*mark;

// 	mark = ft_mark_operator(str);
	
// }

char	is_and_or(char c)
{
	return (c == '|' || c == '&');
}



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
	printf("mark:%s\n", mark);
	splt = upgrade_split(str, mark);
	if (need_split(mark))
	{
		i = -1;
		while (splt[++i])
		{
			printf("HERE:%s.\n", splt[i]);
			remove_surrounded_sp(&splt[i]);
			if (splt[i][0] != '|' && splt[i][0] != '&')
				check_syntax_error(splt[i]);
			// if (splt[i + 1] && is_operator(splt[i][ft_strlen(splt[i]) - 1]) && is_operator(splt[i + 1][0]))
			// {
			// 	if (!(is_and_or(splt[i][ft_strlen(splt[i]) - 1]) && is_redi(splt[i + 1][0])))
			// 			return (1);
			// }
			//printf("ss:%c\n", splt[i][ft_strlen(splt[i]) - 1]);
			if (is_operator(splt[i][0]) && !splt[i + 1])
				return (1);
		}
		//free_ptr(splt);
	}
	else
	{
		if (str)
		{
			remove_surrounded_sp(&str);
			printf("%s|\n", str);
			if (str[ft_strlen(str) - 1] == '>' || str[ft_strlen(str) - 1] == '<')
				return (1);
			str = reform_redirection(str);
			printf("str:%s\n", str);
			if (unvalid_next_parenthesis(str))
				return (1);
			mark = mark_redirection(str, 1);// 1 for spliting with spaces
			splt = upgrade_split(str, mark);
			// >> << > <
			if (need_split(mark))
			{
				i = -1;
				while (splt[++i])
				{
					if (is_operator(splt[i][0]) && (!splt[i + 1] || is_operator(splt[i + 1][0])))
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

// int	oper_last(char *str)
// {
// 	char	*mark;
// 	char	**splt;

// 	mark = 
	
// }

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
**************************************************************************************************
*/

char	is_redi(char c)
{
	return (c == '>' || c == '<');
}

char	is_operator(char c)
{
	return (c == '|' || c == '&');
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

char	*mark_syn_err(char *str)
{
	int		i;
	int		check;
	char 	*mark;

	mark = malloc(ft_strlen(str) * sizeof(char) + 1);
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
			mark[i] = '2';
		else if ((str[i] == '<' || str[i] == '>') && !check)
			mark[i] = '3';
		else if (str[i] == ';' && !check)
			mark[i] = '4';
		else if (str[i] > 32)
			mark[i] = '0';
		else
			mark[i] = '1';
	}
	mark[i] = '\0';
	return (mark);
}
//splti with spce an evrything else if splt[i] == oper && splt[i+1] ==oper ->syntax error

char	*remove_spaces(char *str)
{
	int		i;
	int		j;
	char	*rtn;

	i = -1;
	j = 0;
	while (str[++i])
	if (str[i] > 32)
		j++;
	rtn = malloc(j + 1);
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] > 32)
			rtn[++j] = str[i];
	rtn[++j] = '\0';
	return (rtn);
}

char	unvalid_oper_red(char *mark)
{
	int		i;
	char	check[3];

	i = -1;
	ft_bzero(check, 3);
	while (mark[++i])
	{
		if (mark[i] == '4')
			return (1);
		if (check[1] > 2 || check[0] > 2)
			return (1);
		if (mark[i] == '2')
		{
			if (check[0] || (check[1] && check[2]))
				return (1);
			check[1]++;
			check[2] = 0;
 		}
		if (mark[i] == '3')
		{
			check[0]++;
			check[2] = 0;
		}
		if (mark[i] == '0')
			ft_bzero(check, 3);
		if (mark[i] == '1')
			check[2]++;
	}
	return (check[1] || check[0]);
}

char	unvalid_next_parenthesis(char *str)
{
	int		i;
	int		flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		ft_flag(str[i], &flag);
		//printf("flag:%d, is_operetor:%d, str[%d]:%c, str[%d]:%c\n", flag, is_operator(str[i]), i, str[i], i+1, str[i + 1]);
		if (!flag && !is_operator(str[i]) && str[i] != '(' && str[i + 1] == '(')
			return (1);
		if (!flag && str[i] == '(')
			if (is_operator(str[i + 1]))
				return (printf("HERE\n"), 1);
		if (!flag && str[i] == ')')
			if (str[i + 1] && !is_operator(str[i + 1]) && !is_redi(str[i + 1]) && str[i + 1] != ')')
				return (1);
	}
	return (0);
}

char	*mark_more_arg(char *str)
{
		int		i;
	int		check;
	char 	*mark;

	mark = malloc(ft_strlen(str) * sizeof(char) + 1);
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
			mark[i] = '2';
		else if ((str[i] == '<' || str[i] == '>') && !check)
			mark[i] = '3';
		else if (str[i] == ')' && !check)
			mark[i] = '4';
		else if (str[i] > 32)
			mark[i] = '0';
		else
			mark[i] = '1';
	}
	mark[i] = '\0';
	return (mark);
}

char	red_more_arg(char *str)
{
	char	*mark;
	int		i;
	char	**splt;

	i = -1;
	mark = mark_more_arg(str);
	splt = upgrade_split(str, mark);
	while (splt && splt[++i])
	{
		if (splt[i][0] == ')' && splt[i + 1] && is_redi(splt[i + 1][0]))
		{
			i++;
			if (splt[i + 1] && !is_operator(splt[i + 1][0]))
				if (splt[i + 2] && !is_operator(splt[i + 2][0]) && !is_redi(splt[i + 2][0]))
					return (1);
		}
	}
	return (0);
}

int	syntax_error(char *str)
{
	char	*mark;

	if (emty_parenthesis(str) || unclosed_parenthesis(str) || unclosed_quote(str))
		return (1);
	mark = mark_syn_err(str);
	if (unvalid_oper_red(mark))
		return (free(mark), 1);
	free(mark);
	mark = remove_spaces(str);
	if (is_operator(mark[0]))
		return (1);
	if (unvalid_next_parenthesis(mark))
		return (free(mark), 1);
	if (red_more_arg(str))
		return (1);
	return (0);
}
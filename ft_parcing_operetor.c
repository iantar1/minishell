/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing_operetor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:25:43 by iantar            #+#    #+#             */
/*   Updated: 2023/03/21 12:18:35 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_needle(char *str, char *needle)
{
	int	i;
	int	len_needle;

	i = 0;
	if (!str || !needle)
		return (0);
	while (str[i])
	{
		if (ft_strncmp(str + i, needle, ft_strlen(needle)))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_mark1(char *str)
{
	int		i;
	char	*mark;
	char	check;

	if (!str)
		return (NULL);
	mark = malloc(sizeof(char) * ft_strlen(str) + 1);
	check = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (str[i] == check)
				check = 0;
			else if (!check)
				check = str[i];
		}
		if (!check && str[i] == '(')
			check = str[i];
		if (check == '(' && str[i] == ')')
			check = 0;
		if ((str[i] == '|' || str[i] == '&') && !check)
			mark[i] = '2';
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
}
//you must check the syntax error befor using this function, str must not start with | or &. or has '|&'
char	*mark_the_mark1_operator(char *mark)//split with the last && or ||
{
	int		len;
	char	*mark;
	int		check;

	len = ft_strlen(mark) - 1;
	check = 1;
	while (len >= 0)
	{
		if ((mark[len] == '2' && mark[len - 1] == '2') && check)
		{
			mark[len--] = '2';
			mark[len--] = '2';
			check = 0;
		}
		else
			mark[len--] = '0';
	}
	return (mark);
}

char	**mark_first_parenthisis(char *str)//to remove the first parenthesis.(ls | cat > out (cat out | wc)) -> ls | cat > out (cat out | wc)
{
	int		check;
	int		i;
	char	*mark;

	mark = malloc(sizeof(char) * (ft_strlen(str) - 1));
	i = 0;
	check = 0;
	while (str[i])
	{
		if ((str[i] <= 32 || str[i] == '(') && !check)
		{
			mark[i] = '2';
			if (str[i] == '(')
				check++;
		}
		else if (str[i] == ')' && check == 1)
			mark[i] = '2';
		else
			mark[i] = '0';
		i++;
		
	}
	mark[i] = '\0';
}

int	main()
{
	char str[10] = "0220022002"
	printf("%s")
}

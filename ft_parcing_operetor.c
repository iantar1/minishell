/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing_operetor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:25:43 by iantar            #+#    #+#             */
/*   Updated: 2023/03/17 19:07:12 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here(char *str, char *needle)
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

char	*mark_logic_operator()//split && and ||

// void	modify_mark(char **str)
// {
// 	int	len;

// 	len = ft_srtle(*str);
// 	if (is_here(*str, "22"))
// 	{
// 		while (--len >= 0)
// 		{
// 			if (*(*str + len) == '2' && *(*str + len - 1) == '2')
// 			{
// 				len--;
// 				while (--len >= 0)
// 					*(*str + len) = '0';
// 			}
// 		}
// 	}
// 	else
// 	{
// 		while (len >= 0)
// 		{
// 			if (*(*str + len) == '2')
// 				while (--len >= 0)
// 					*(*str + len) = '0';
// 			len--;
// 		}
// 	}
// }

int	main()
{
	char str[10] = "0220022002"
	printf("%s")
}

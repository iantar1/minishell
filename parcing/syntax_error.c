/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:14:00 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 16:11:28 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	surnd_parnt(char *str)
{
	char	*mark;
	char	*tmp;

	tmp = strtrim_upgrade(str, "	 ");
	mark = mark_first_parenthisis(tmp);
	if (surrounded_parenthisis(mark))
		return (1);
	return (0);
}

int	check_syntax(char *str)
{
	if (emty_parenthesis(str)
		|| unclosed_parenthesis(str) || unclosed_quote(str))
		return (1);
	if (invalid_oper1(str))
		return (1);
	if (invalid_oper2(str))
		return (1);
	if (invalid_oper3(str))
		return (1);
	if (invalid_red1(str))
		return (1);
	if (invalid_red2(str))
		return (1);
	if (invalid_red3(str))
		return (1);
	if (invalid_next_red(str))
		return (1);
	if (unvalid_next_open_parth(str))
		return (1);
	if (invalide_char(str))
		return (1);
	return (0);
}

int	recur_check(char *(*marker)(char *, int), char(*is_red_opr)(char),
				char *str)
{
	char	*mark;
	int		i;
	char	**splt;

	mark = marker(str, 0);
	mark = ft_mark_operator(str, 0);
	if (!need_split(mark))
		mark = mark_redirection(str, 0);
	splt = upgrade_split(str, mark);
	i = -1;
	if (need_split(mark))
	{
		while (splt[++i])
		{
			if (!is_red_opr(splt[i][0]))
			{
				if (syntax_error(splt[i], 0))
					return (1);
			}
		}
	}
	return (0);
}

int	syntax_error(char *str, int check)
{
	char	*tmp;

	if (check && check_syntax(str))
		return (1);
	if (unvalid_next_close_parth(str))
		return (1);
	while (surnd_parnt(str))
		remove_first_parenthisis(&str);
	if (recur_check(ft_mark_operator, is_operator, str))
		return (1);
	tmp = str;
	str = reform_redirection(str);
	if (recur_check(mark_redirection, is_redi, str))
		return (1);
	return (0);
}

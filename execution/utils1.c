/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:22:47 by iantar            #+#    #+#             */
/*   Updated: 2023/05/13 11:07:42 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

void	handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_dprintf(1, "\n");
		sv_exit(130);
	}
	else
	{
		ft_dprintf(1, "Quit:3\n");
		sv_exit(131);
	}
}

int	oi_atoi(const char *str)
{
	int				i;
	int				minus_count;
	unsigned long	num;

	i = 0;
	minus_count = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		minus_count -= 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i++] - '0';
		if (num > __LONG_MAX__)
			return (0 - (minus_count == 1));
	}
	return (num * minus_count);
}

//exit(exit_status);
int	sv_exit(int exit_status)
{
	char	*str;

	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	str = oi_itoa(exit_status);
	modify_env_var("?", str);
	if (str)
		free(str);
	return (exit_status);
}

char	get_mark(char c, int *check1, int *check2)
{
	char	mark;

	if (c == 34)
	{
		*check1 += 1;
		mark = '0';
	}
	if (c == 39)
	{
		*check2 += 1;
		mark = '0';
	}
	else if (*check1 % 2 || *check2 % 2 || (c > 32 || c < 0))
		mark = '0';
	else
		mark = '1';
	return (mark);
}

char	*oi_mark(char *str)
{
	int		i;
	char	*mark;
	int		check1;
	int		check2;

	if (!str)
		return (NULL);
	mark = malloc(sizeof(char) * (oi_strlen(str) + 1));
	i = -1;
	check1 = 0;
	check2 = 0;
	while (str[++i])
		mark[i] = get_mark(str[i], &check1, &check2);
	mark[i] = '\0';
	return (mark);
}

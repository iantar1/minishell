/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:54:22 by oidboufk          #+#    #+#             */
/*   Updated: 2023/11/10 22:18:05 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	ft_isalpha_num(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

int	handle_export(char *str)
{
	int		i;
	char	**splited;

	i = 1;
	splited = oi_split(str, '=');
	if (!splited || !str || str[0] == '=' || !ft_isalpha(splited[0][0])
		|| !splited[0] || splited[0][0] == '+')
		return (ft_dprintf(2, "bash: export: `%s': not a \
valid identifier\n", str), (splited && (free_now(splited), 0)), sv_exit(1));
	while (splited[0][i])
	{
		if ((!ft_isalpha_num(splited[0][i]) && splited[0]
			[oi_strlen(splited[0]) - 1] != '+') || !splited[0])
		{
			ft_dprintf(2, "bash: export: `%s': not a valid identifier\n", str);
			if (splited)
				free_now(splited);
			return (sv_exit(1));
		}
		i++;
	}
	if (splited )
		free_now(splited);
	return (0);
}

int	handle_unset(char *str)
{
	int	i;

	if (!str || !str[0] || !ft_isalpha(str[0]))
	{
		ft_dprintf(2, "bash: unset: `%s': not a valid identifier\n", str);
		return (sv_exit(1), -1);
	}
	i = 0;
	while (str[++i])
	{
		if (!str || !str[0] || !ft_isalpha_num(str[i]))
		{
			ft_dprintf(2, "bash: unset: `%s': not a valid identifier\n", str);
			return (sv_exit(1), -1);
		}
	}
	return (0);
}

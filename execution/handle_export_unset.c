/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_export_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:54:22 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/10 19:48:10 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	handle_export(char *str)
{
	int		i;
	char	**splited;

	i = 0;
	splited = oi_split(str, '=');
	if (!splited || !splited[0] || splited[0][0] == '+')
		return (ft_dprintf(2, "bash: export: `%s': not a \
valid identifier\n", str), sv_exit(1), -1);
	while (splited[0][i])
	{
		if ((!ft_isalpha(splited[0][i])
			&& splited[0][oi_strlen(splited[0]) - 1] != '+') || !splited[0])
		{
			ft_dprintf(2, "bash: export: `%s': not a valid identifier\n", str);
			return (ft_free(splited), sv_exit(1));
		}
		i++;
	}
	return (ft_free(splited), 0);
}

int	handle_unset(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]))
		{
			ft_dprintf(2, "bash: unset: `%s': not a valid identifier\n", str);
			return (sv_exit(1), -1);
		}
	}
	return (0);
}

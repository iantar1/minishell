/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:37:49 by iantar            #+#    #+#             */
/*   Updated: 2023/03/03 18:38:59 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//$?$?"$|$$$%
void	
int	need_expand(char *str)
{
	if (!str || str[0] != '$')
		return (0);
	if (str[1] == '?')
		return (-1);
	if (str[1] < 65 || (str[1] > 90 && str[1] < 97) || str[1] > 122)
		return (0);
	return (1);
}

char	*expand(char *key, t_env *head_env, char exit_status)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = head_env;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->var_name, ft_strlen(key)))
			return (tmp->line);
		tmp = tmp->next;
	}
	return (NULL);
}

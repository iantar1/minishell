/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:39:20 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/13 13:55:13 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

void	rm_var(char *str)
{
	t_env	*tmp;
	t_env	*head;

	head = g_env;
	tmp = NULL;
	while (g_env)
	{
		if (!oi_strcmp(str, g_env->var_name))
		{
			if (tmp)
				tmp->next = g_env->next;
			(free(g_env->var_name), free(g_env->line), free(g_env));
			g_env = head;
			return ;
		}
		tmp = g_env;
		g_env = g_env->next;
	}
	g_env = head;
}

int	unset_var(t_tree *tree)
{
	int		i;

	i = 0;
	while (tree->data.args[++i])
	{
		if (handle_unset(tree->data.args[i]))
			continue ;
		rm_var(tree->data.args[i]);
	}
	if (g_env)
		from_list_to_char(1);
	return (modify_env_var("_", "unset"), 0);
}

int	is_num(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data cmd)
{
	if (len_double_char(cmd.args) > 2)
	{
		ft_dprintf(2, "exit\n");
		if (is_num(cmd.args[1]) || !cmd.args[1][0])
			return (ft_dprintf(2, "Numirecal arg required"), sv_exit(1));
		ft_dprintf(2, "exit : too many argiments\n");
		return (sv_exit(1));
	}
	else if (len_double_char(cmd.args) > 1)
	{
		if (is_num(cmd.args[1]) && cmd.args[1][0])
		{
			ft_dprintf(2, "exit\n");
			exit(sv_exit(oi_atoi(cmd.args[1])));
		}
		else
		{
			ft_dprintf(2, "exit\n%s : numeric argument required!\n", cmd.args[1]);
			exit(sv_exit(255));
		}
	}
	else
		exit(sv_exit(oi_atoi(get_env_line("?"))));
	return (modify_env_var("_", "exit"), 0);
}

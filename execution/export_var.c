/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:31:06 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/11 16:27:44 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

t_env	*env_last(t_env *env)
{
	if (!env)
		return (0);
	while (env->next)
		env = env->next;
	return (env);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (env)
	{
		if (!*env)
			*env = new;
		else
		{
			last = env_last(*env);
			last->next = new;
		}
	}
}

// size_t	len_double_char(char **strs)
// {
// 	size_t	i;

// 	if (!strs)
// 		return (0);
// 	i = 0;
// 	while (strs[i])
// 		i++;
// 	return (i);
// }

// var+="1234"

int	add_to_env(char	**key_value)
{
	char	**var;
	t_env	*new;
	char	*trim;
	char	*line;

	line = oi_strdup(*key_value);
	var = get_key_value_oi(*key_value);
	trim = oi_strtrim(var[0], "+");
	if (!is_in_env(trim))
	{
		new = new_line_oi(line);
		env_add_back(&g_env, new);
	}
	else
	{
		if (var && var[1])
			modify_var(var);
	}
	return (free(line), free_now(var), free(trim), 1);
}

int	export_var(t_tree *tree)
{
	int		i;
	t_env	*tmp;
	int		st;
	int		sv;

	sv = 0;
	if (!oi_strcmp(tree->data.cmd, "export")
		&& len_double_char(tree->data.args) == 1)
		show_env_in_order();
	else if (len_double_char(tree->data.args) > 1)
	{
		i = 0;
		tmp = g_env;
		while (tree->data.args[++i])
		{
			st = handle_export(tree->data.args[i]);
			if (st)
				sv = st;
			if (st)
				continue ;
			g_env = (add_to_env(&tree->data.args[i]), tmp);
		}
		from_list_to_char(1);
	}
	return (sv);
}

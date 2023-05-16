/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utiles2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:40:50 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/15 16:15:27 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

int	oi_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

int	oi_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i] &&
	(((unsigned char *)s1)[i] != '\0' ||
	((unsigned char *)s2)[i] != '\0') && i < n)
	{
		i++;
	}
	if (i < n)
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	return (0);
}

char	*get_variable(char *str)
{
	char	*var;
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (str[len] && str[len] != '=')
		len++;
	var = malloc(len);
	while (str[i] && str[i] != '=')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

int	handle_cmd_2(t_tree *tree, int out)
{
	char	*cwd;

	if (!oi_strcmp(tree->data.cmd, "cd"))
		return (cd(tree, out));
	else if (!oi_strcmp(tree->data.cmd, "pwd"))
	{
		cwd = pwd();
		modify_env_var("_", "cd");
		return ((cwd) && ft_dprintf(out, "%s\n", cwd) && (free(cwd), 0), 0);
	}
	else if (!oi_strcmp(tree->data.cmd, "export"))
		return (export_var(tree, out));
	else if (!oi_strcmp(tree->data.cmd, "unset"))
		return (unset_var(tree));
	else if (!oi_strcmp(tree->data.cmd, "exit"))
		return (ft_exit(tree->data));
	else if (!oi_strcmp(tree->data.cmd, "echo"))
		return (echo(tree, out), 0);
	return (1);
}

int	handle_cmd(t_tree *tree, int out)
{
	t_env		*tmp;
	int			st;
	struct stat	fd_state;

	if (!tree->data.cmd)
		return (0);
	tmp = g_env;
	if (fstat(out, &fd_state) == -1)
		out = 1;
	if (!oi_strcmp(tree->data.cmd, "env"))
	{
		modify_env_var("_", "env");
		if (len_double_char(tree->data.args) > 1)
			return (ft_dprintf(2, "too many args !\n"), 0);
		while (g_env)
		{
			if (g_env->line && oi_strcmp(g_env->var_name, "?"))
				ft_dprintf(out, "%s=%s\n", g_env->var_name, g_env->line);
			g_env = g_env->next;
		}
	}
	g_env = tmp;
	st = handle_cmd_2(tree, out);
	return (st);
}

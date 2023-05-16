/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:27:08 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/15 13:01:49 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

char	*loop_path(char *cmd, int print, char **paths)
{
	int		i;
	char	*cmd1;
	char	*full_path;

	if (!paths || !paths[0])
		return (NULL);
	if (oi_strchr(cmd, '/'))
		return (free_now(paths), cmd);
	i = 1;
	cmd1 = classic_ft_strjoin("/", cmd);
	full_path = classic_ft_strjoin(paths[0], cmd1);
	if (!access(full_path, X_OK))
		return (free_now(paths), free(cmd1), full_path);
	while (paths && paths[i] && access(full_path, X_OK))
		full_path = (free(full_path), classic_ft_strjoin(paths[i++], cmd1));
	if (!is_builtin(cmd) && (!paths || !paths[i]))
	{
		print_exec_errors(full_path, cmd, print);
		return (free_now(paths), free(cmd1)
			, (full_path && (free(full_path), 0)), NULL);
	}
	return (free_now(paths), free(cmd1), full_path);
}

/// @brief gets the path for the execve system call
/// @param cmd  is the command to check the path for
/// @param Path the $PATH from env variable
/// @param print represents bool either to print the error 
///          like (ll: command not found)
/// @return the returned path (NULL in case no path found)
char	*get_path(char *cmd, char *Path, int print)
{
	char	**paths;
	char	*check;
	int		count;

	count = 0;
	if (((!access(cmd, X_OK) || !access(cmd, F_OK)) && !Path)
		|| ((!access(cmd, X_OK) || !access(cmd, F_OK))
			&& oi_strchr(cmd, '/') && Path))
		count++;
	paths = oi_split(Path, ':');
	if ((!paths || !paths[0]) && (print & !count))
		return (print_exec_errors(NULL, cmd, print), NULL);
	check = loop_path(cmd, print, paths);
	if (count && check && cmd[0] != '.'
		&& !oi_strchr(cmd, '/'))
		return (check);
	else if (count && (!check || cmd[0] == '.' || oi_strchr(cmd, '/')))
		return (oi_strdup(cmd));
	else if (!count && check && oi_strchr(cmd, '/'))
		return (oi_strdup(check));
	else if (!count && check)
		return (check);
	return (NULL);
}

int	modify_env_var(char	*var_name, char *new_val)
{
	t_env	*tmp;

	tmp = g_env;
	while (g_env)
	{
		if (!oi_strcmp(g_env->var_name, var_name) && var_name)
		{
			if (g_env->line)
				free(g_env->line);
			g_env->line = oi_strdup(new_val);
			g_env = tmp;
			return (g_env = tmp, 0);
		}
		else if (!g_env->next)
		{
			g_env->next = malloc(sizeof(t_env));
			g_env->next->var_name = oi_strdup(var_name);
			g_env->next->line = oi_strdup(new_val);
			g_env->next->next = NULL;
			break ;
		}
		g_env = g_env->next;
	}
	g_env = tmp;
	return (-1);
}

char	*get_env_line(char *var_name)
{
	t_env	*tmp;
	char	*line;

	tmp = g_env;
	line = NULL;
	while (g_env)
	{
		if (!oi_strcmp(var_name, g_env->var_name) && var_name)
		{
			if (g_env->line)
				free(line);
			line = oi_strdup(g_env->line);
			break ;
		}
		g_env = g_env->next;
	}
	g_env = tmp;
	return (line);
}

int	update_env(char	*cmd, char *val)
{
	char	*line;
	char	*path;

	line = get_env_line("PATH");
	path = get_path(cmd, line, 1);
	if (!oi_strcmp(cmd, "cd"))
		modify_env_var("PWD", val);
	if (path)
		(modify_env_var("_", path), free(path));
	if (line)
		free(line);
	return (0);
}

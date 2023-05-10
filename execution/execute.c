/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:53:43 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/10 14:51:14 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

int	is_builtin(char *str)
{
	if (!oi_strcmp(str, "cd"))
		return (1);
	else if (!oi_strcmp(str, "pwd"))
		return (1);
	else if (!oi_strcmp(str, "echo"))
		return (1);
	else if (!oi_strcmp(str, "env"))
		return (1);
	else if (!oi_strcmp(str, "exit"))
		return (1);
	else if (!oi_strcmp(str, "export"))
		return (1);
	else if (!oi_strcmp(str, "unset"))
		return (1);
	return (0);
}

int	is_directory(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	print_exec_errors(char *full_path, char *cmd, int print)
{
	if (!full_path)
		return (ft_dprintf(2, "%s :%s\n", cmd, "command not found"), 127);
	if (!is_builtin(cmd) && (((free(full_path), 1) && print) || print == 3))
	{
		if (access(cmd, X_OK) && !access(cmd, F_OK) && cmd[0] == '.')
			return (ft_dprintf(2, "%s :%s\n", cmd, "Permission denied"), 126);
		else if (((access(cmd, X_OK) && !oi_strchr(cmd, '/'))
				|| !oi_strcmp(cmd, "..")) && print != 3)
			return (ft_dprintf(2, "%s :%s\n", cmd, "command not found"), 127);
		else if (oi_strchr(cmd, '/') || print == 3)
		{
			if (!is_directory(cmd))
				return (ft_dprintf(2, "%s :No such file or directory\n"
						, cmd), 1);
			else
				return (ft_dprintf(2, "%s :%s\n", cmd, " is a directory"), 126);
		}
		else
			return (perror(cmd), errno);
	}
	return (0);
}
// the execute function needs to be modified.  
// _first) wait is after the (&& , || , the last cmd)

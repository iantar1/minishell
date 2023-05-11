/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:13:58 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/11 15:11:03 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

#define FLAG 0
#define NOT_FLAG 1

int	complete_cd(t_tree *tree, char **home)
{
	if (!(len_double_char(tree->data.args) >= 2
			&& oi_strcmp(tree->data.args[1], "~")))
	{
		*home = get_env_line("HOME");
		if (!*home || !*home[0])
			return (ft_dprintf(2, "cd : HOME not set. \n"), sv_exit(1));
	}
	if (chdir(*home))
		return (perror(*home), free_oi(home, 0), sv_exit(1));
	else
		(sv_exit(0), free_oi(home, 0));
	return (0);
}

int	cd(t_tree *tree, int out)
{
	char	*home;
	char	*cwd;
	int		st;

	cwd = pwd();
	st = 0;
	if (len_double_char(tree->data.args) >= 2
		&& oi_strcmp(tree->data.args[1], "~"))
	{
		if (!oi_strcmp(tree->data.args[1], "-"))
		{
			home = get_env_line("OLDPWD");
			if (!home || !home[0])
				return (ft_dprintf(2, "OLDPWD is NOT set!\n"), sv_exit(1));
			ft_dprintf(out, "%s\n", home);
		}
		else
			home = oi_strdup(tree->data.args[1]);
	}
	st = complete_cd(tree, &home);
	if (!st)
		(modify_env_var("OLDPWD", cwd));
	cwd = (((cwd) && (free(cwd), 0)), pwd());
	(modify_env_var("PWD", cwd), ((cwd) && (free(cwd), 0)));
	return (st);
}

char	*pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		return (sv_exit(1), get_env_line("PWD"));
	return (sv_exit(0), oi_strdup(cwd));
}

int	echo_flags(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (NOT_FLAG);
	if (str[i] == '-')
	{
		while (str[i++])
		{
			if (str[i] != c)
				break ;
		}
		if (!str[i] && str[i - 1] != '-')
			return (FLAG);
		else
			return (NOT_FLAG);
	}
	return (NOT_FLAG);
}

void	echo(t_tree *tree, int out)
{
	int		i;

	i = 1;
	while (tree->data.args[i] && echo_flags(tree->data.args[i], 'n') == FLAG)
		i++;
	while (tree->data.args[i])
	{
		ft_dprintf(out, "%s", tree->data.args[i++]);
		if (tree->data.args[i])
			ft_dprintf(out, " ");
	}
	if (!tree->data.cmd || echo_flags(tree->data.args[1], 'n') == NOT_FLAG)
		ft_dprintf(out, "\n");
	(sv_exit(0));
}

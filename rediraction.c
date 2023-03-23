/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:45:25 by iantar            #+#    #+#             */
/*   Updated: 2023/03/23 12:47:36 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//you need to modify the cmd before spliting "ls > out -l" becames "ls -l > out"
// cat > outfile file1 file2... -> cat file1 file2 ... > outfile
//creat a functin take the args after the arg after > or < to the front of the cmd
// cmd < arg1 arg2 arg3 ...  -->  cmd  arg2 arg3 ... < arg1
// cmd > arg1 arg2 arg3 ...  -->  cmd  arg2 arg3 ... > arg1

static char	*mark_redirection(char *str)
{
	int		i;
	char	*mark;

	i = 0;
	mark = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			mark[i] = '2';
		if (str[i] <= 32)
			mark[i] = '1';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

static int	ft_pointerlen(char **ptrs)
{
	int	lenptr;

	lenptr = 0;
	while (ptrs[lenptr])
		lenptr++;
	return (lenptr);
}

static int	index_of_redir(char **splt_cmd)
{
	int	index;

	index = 0;
	while (splt_cmd[index])
	{
		if (ft_strncomp(splt_cmd[index], ">>", ft_strlen(splt_cmd[index]))
			|| ft_strncomp(splt_cmd[index], "<<", ft_strlen(splt_cmd[index])))
			return (index);
		index++;
	}
	return (-1);
}

char	**reform_redirection(char *str)
{
	char	**splt_cmd;
	char	**rtn_cmd;
	char	*mark;
	t_vars	var;

	mark = mark_redirection(str);
	splt_cmd = upgrade_split(str, mark);
	rtn_cmd = malloc((ft_pointerlen(splt_cmd) + 1) * sizeof(char *));
	var.index = index_of_redir(splt_cmd);
	while (splt_cmd[var.i])
	{
		if (var.i == var.index && var.index + 2 < ft_pointerlen(splt_cmd))
				var.j = var.index + 2;
		rtn_cmd[var.i] = splt_cmd[var.j];
		(var.j)++;
		(var.i)++;
	}
	rtn_cmd[var.i] = NULL;
	free(splt_cmd);
	return (rtn_cmd);
}


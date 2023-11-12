/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:15:35 by iantar            #+#    #+#             */
/*   Updated: 2023/11/10 21:56:01 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_oi.h"

int	there_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			return (1);
		i++;
	}
	return (0);
}

void	change_fill_splt(char **splt, char *name)
{
	int	i;
	int	len_her;

	i = 0;
	len_her = count_heredoc(splt);
	while (splt[i])
	{
		if (!ft_strcmp(splt[i], "<<") && len_her > 1)
		{
			splt[i] = (NULL);
			i++;
			splt[i] = (NULL);
			len_her--;
		}
		else if (!ft_strcmp(splt[i], "<<") && len_her == 1)
		{
			i++;
			splt[i] = name;
			break ;
		}
		i++;
	}
}

void	change_line(char **splt, char **line, int len)
{
	int		i;

	i = 0;
	while (!splt[i])
		i++;
	*line = splt[i];
	while (++i < len)
	{
		if (splt[i])
		{
			*line = strjoin_upgrade(*line, " ");
			*line = strjoin_upgrade(*line, splt[i]);
		}
	}
}

char	*heredoc_expanding(char *str, char *lim)
{
	char	**splt;
	t_vars	var;
	int		len_splt;

	var.i = -1;
	if (!str)
		return (NULL);
	if (there_quote(lim))
		return (str);
	splt = upgrade_split(str, expand_mark(str));
	len_splt = len_ptr(splt);
	while (splt[++(var.i)])
	{
		var.j = -1;
		ft_expand_norm(var, splt);
	}
	return (_join_evrything_(splt, len_splt));
}

int	sendherdoc_getfd(int to_save, int fds)
{
	char	*name;
	char	*new_name;
	int		fd;

	if (to_save)
	{
		name = heredoc_filename();
		new_name = strjoin_upgrade("/tmp/", name);
		write(fds, new_name, ft_strlen(new_name));
		close(fds);
		fd = open(new_name, O_TRUNC | O_RDWR | O_CREAT, 0666);
		if (fd == -1)
		{
			write(2, "minishell:file can't open\n", 26);
			modify_env_var("?", "1");
			return (0);
		}
	}
	else
		fd = -1;
	return (fd);
}

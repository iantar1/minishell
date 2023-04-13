/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:55:57 by iantar            #+#    #+#             */
/*   Updated: 2023/04/13 06:49:55 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*red_mark(char *str, int sp)
{
	int		i;
	int		flag;
	char	*mark;

	i = 0;
	flag = 0;
	mark = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		ft_flag(str[i], &flag);
		if (!flag && str[i] == '>')
			mark[i] = '2';
		else if (!flag && str[i] == '<')
			mark[i] = '3';
		else if (str[i] <= 32 && sp)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

int	count_red(char **splt, char red)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (splt[i])
	{
		if (splt[i][0] == red)
			cnt++;
		i++;
	}
	return (cnt);
}

void	keep_last_redir(char **line)
{
	char	*mark;
	char	**splt;
	int		len;
	int		i;
	int		fd;
	int		len_in;
	int		len_out;

	i = -1;
	if (!*line)
		return ;
	printf("LINE:%s\n", *line);
	mark = red_mark(*line, SPACE);
	splt = upgrade_split(*line, mark);
	mark = *line;
	len = len_ptr(splt);
	len_out = count_red(splt, '>');
	len_in = count_red(splt, '<');
	while (splt[++i])
	{
		if (!ft_strcmp(splt[i], ">>"))
		{
			fd = open(splt[i + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
			if (fd < 0)
			{
				write(2, "minishell:file can't open\n", 26);
				// modify_var("?", "1");
				return ;
			}
			close(fd);
			if (len_out > 1)
			{
				splt[i] = (free(splt[i]), NULL);
				i++;
				splt[i] = (free(splt[i]), NULL);
			}
			len_out--;
		}
		else if (!ft_strcmp(splt[i], ">"))
		{
			fd = open(splt[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (fd < 0)
			{
				write(2, "minishell:file can't open\n", 26);
				// modify_var("?", "1");
				return ;
			}
			close(fd);
			if (len_out > 1)
			{
				splt[i] = (free(splt[i]), NULL);
				i++;
				splt[i] = (free(splt[i]), NULL);
			}
			len_out--;
		}
		else if (!ft_strcmp(splt[i], "<"))
		{
			if (len_in > 1)
			{
				splt[i] = (free(splt[i]), NULL);
				i++;
				splt[i] = (free(splt[i]), NULL);
			}
			len_in--;
		}
	}
	i = 0;
	//free(mark);
	while (!splt[i])
		i++;
	*line = splt[i];
	while (++i < len)
	{
		if (splt[i])
		{
			mark = *line;
			*line = ft_strjoin(*line, " ");
			free(mark);
			mark = *line;
			*line = ft_strjoin(*line, splt[i]);
			//splt[i] = NULL;
			free(mark);
		}
	}
	free(splt);
}
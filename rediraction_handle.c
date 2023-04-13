/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction_handle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:55:57 by iantar            #+#    #+#             */
/*   Updated: 2023/04/13 02:46:13 by iantar           ###   ########.fr       */
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

void	keep_last_redir(char **line)
{
	char	*mark;
	char	**splt;
	int		len;
	int		i;
	int		fd;
	int		len_in;
	int		len_out;

	//use the reform_redirection(line) here
	//the convert **p to a str , and asing it to *line
	i = -1;
	if (!*line)
		return ;
	mark = red_mark(*line, SPACE);//we don
	splt = upgrade_split(*line, mark);
	mark = *line;
	len = len_ptr(splt);
	len_out = count_out(splt);
	len_in = count_in(splt);
	while (splt[++i])
	{
		if (!ft_strcmp(splt[i], ">>"))
		{
			fd = open(splt[i + 1], O_RDWR, O_APPEND, O_CREAT, 0644);
			if (fd < 0)
			{
				write(2, "minishell:file can't open\n", 26);
				// modify_var("?", "1");
			}
		}
		if (!ft_strcmp(splt[i], ">"))
		{
			open(splt[i + 1], O_RDWR| O_TRUNC | O_CREAT, 0644);
			if (fd < 0)
			{
				write(2, "minishell:file can't open\n", 26);
				// modify_var("?", "1");
			}
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
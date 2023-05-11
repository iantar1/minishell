/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:32:28 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 14:35:17 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_oi.h"

int	here_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] == '\n' && !s2[i])
			return (0);
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*heredoc_filename(void)
{
	char	*name;
	char	*buf;
	int		fd;
	int		ij[2];

	buf = upgrade_malloc(51, 0);
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		modify_env_var("?", "1");
		return (write(2, "minishell:file can't open\n", 26), NULL);
	}
	if (read(fd, buf, 50) == -1)
		return (NULL);
	buf[50] = (close(fd), '\0');
	name = upgrade_malloc(6, 0);
	ij[0] = -1;
	ij[1] = -1;
	while (buf[++ij[0]] && ij[1] < 4)
		if (ft_isalnum(buf[ij[0]]))
			name[++ij[1]] = buf[ij[0]];
	if (ij[1] == -1)
		return (heredoc_filename());
	name[++ij[1]] = '\0';
	return (name);
}

char	*mark_here_doc(char *str)
{
	int		i;
	int		flag;
	char	*mark;

	i = 0;
	flag = 0;
	mark = upgrade_malloc(sizeof(char) * (ft_strlen(str) + 1), 0);
	while (str[i])
	{
		ft_flag(str[i], &flag);
		if (str[i] == '<' && !flag)
			mark[i] = '2';
		else if ((str[i] == '>' || str[i] == ')') && !flag)
			mark[i] = '3';
		else if (str[i] <= SPACE && str[i] >= 0 && !flag)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

int	count_heredoc(char **splt)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (splt[i])
	{
		if (!ft_strcmp(splt[i], "<<") && splt[i + 1])
			cnt++;
		i++;
	}
	return (cnt);
}

void	keep_last_heredoc(char **line, char *name)
{
	char	*mark;
	char	**splt;
	int		len;

	if (!line || !*line)
		return ;
	mark = mark_here_doc(*line);
	splt = upgrade_split(*line, mark);
	len = len_ptr(splt);
	change_fill_splt(splt, name);
	change_line(splt, line, len);
}

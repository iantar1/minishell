/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:37 by iantar            #+#    #+#             */
/*   Updated: 2023/04/06 03:02:43 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
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

static void	handle_sig(int sig)
{
	(void)sig;
	exit(0);
}

char	*heredoc_filename(void)
{
	static int	here;
	char		*name;
	char		*num;

	if (here == 16)
		here = 0;
	num = ft_itoa(here);
	name = ft_strjoin("her_tmp", num);
	here++;
	free(num);
	return (name);
}

//use reform cmd : >> << > < must be the last
t_heredoc	here_doc(char *lim, int to_save)
{
	char		*line;
	t_heredoc	here;
	char		*name;

	//signal(SIGINT, handle_sig);
	if (to_save)
	{
		name = heredoc_filename();
		here.fd = open(name, O_TRUNC | O_RDWR | O_CREAT, 0666);
		here.filename = name;
		// if (fd == -1)
		// 	return ;
	}
	else
		here.fd = -1;
	line = (write(1, "> ", 2), get_next_line(0));
	while (1)
	{
		if (!line)
			return ;
		if (!ft_strcmp(lim, line))
		{
			free(line);
			return ;
		}
		(write(1, "> ", 2), write(here.fd, line, ft_strlen(line)));
		line = (free(line), get_next_line(0));
	}
	return (here);
}

// open all here_doc and save just the last.

char	*mark_here_doc(char *str)
{
	int		i;
	char	*mark;

	i = 0;
	mark = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
		{
			mark[i] = '2';
			mark[++i] = '2';
		}
		else if (str[i] <= 32)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

void	keep_last_heredoc(char **line, char *name)
{
	char	*mark;
	char	**splt;
	int		len;
	int		i;
	int		len_her;

	i = 0;
	mark = mark_here_doc(line);
	splt = upgrade_split(line, mark);
	mark = *line;
	len = len_ptr(splt);
	len_her = count_heredoc(splt);
	while (splt[i])
	{
		if (!ft_strncmp(splt[i], "<<", ft_strlen(splt[i])) && len_her > 1)
		{
			splt[i] = (free(splt[i]), NULL);
			splt[++i] = (free(splt[i]), NULL);
		}
		i++;
	}
	i = 0;
	*line = splt[i++];
	while (i < len)
	{
		if (splt[i])
			*line = ft_strjoin(*line, splt[i]);
		i++;
	}
}

int	count_heredoc(char **splt)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (splt[i])
	{
		if (!ft_strncmp(splt[i], "<<", ft_strlen(splt[i])) && splt[i + 1])
			cnt++;
		i++;
	}
	return (cnt);
}

t_heredoc	open_heredocs(char *line)//this function will open all the here_docs and will return the last filename_heredoc
{
	t_heredoc	rtn_heredoc;
	char		**splt;
	char		*mark;
	int			num_here;
	int			i;

	signal(SIGINT, handle_sig);
	mark = mark_here_doc(line);
	splt = upgrade_split(line, mark);
	num_here = count_heredoc(splt);
	while (splt[i])
	{
		if (!ft_strncmp(splt[i], "<<", ft_strlen(splt[i])) && num_here > 1)
		{
			here_doc(splt[i + 1], 0);
			num_here--;
		}
		else if (!ft_strncmp(splt[i], "<<", ft_strlen(splt[i]))
			&& num_here == 1)
		{
			rtn_heredoc = here_doc(splt[i + 1], 1);
			num_here--;
		}
		i++;
	}
	return (rtn_heredoc);
}

void	check_here_doc(char **line)
{
	char	*tmp;

	if (!is_here_needle(*line, "<<"))
		return ;
	tmp = *line;
	*line = reform_redirection(*line);
	free(tmp);
}


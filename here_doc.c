/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:37 by iantar            #+#    #+#             */
/*   Updated: 2023/04/12 07:08:53 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	handle_sig(int sig)
{
	(void)sig;
	exit(0);
}

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

char	*heredoc_expanding(char *str, char *lim)
{
	char	**splt;
	t_vars	var;

	var.i = -1;
	if (!str)
		return (NULL);
	if (there_quote(lim))
		return (str);
	splt = upgrade_split(str, expand_mark(str));
	while (splt[++(var.i)])
	{
		var.j = -1;
		ft_expand_norm(var, splt);
	}
	return (join_evrything(splt));
}

char	*heredoc_filename(void)
{
	char	*name;
	char	*buf;
	int		fd;
	int		i;
	int		j;

	buf = malloc(21);
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (NULL);
	read(fd, buf, 20);
	close(fd);
	buf[20] = '\0';
	name = malloc(6);
	i = -1;
	j = -1;
	while (buf[++i] && j < 5)
	{
		if (ft_isalnum(buf[i]))
			name[++j] = buf[i];
	}
	name[++j] = '\0';
	free(buf);
	return (name);
}

char	*her_doc(char *lim, int to_save)
{
	char	*line;
	char	*name;
	int		fd;
	char	*new_lim;
	char	*here_exp;

	new_lim = remove_quote(lim);
	if (to_save)
	{
		name = heredoc_filename();
		fd = open(name, O_TRUNC | O_RDWR | O_CREAT, 0666);
		if (fd == -1)
			return (NULL);
	}
	else
	{
		fd = -1;
		name = NULL;
	}
		
	line = (write(1, "> ", 2), get_next_line(0));
	while (1)
	{
		if (!line)
			return (close(fd), name);
		if (!here_strcmp(line, new_lim))
		{
			free(line);
			return (close(fd), name);
		}
		here_exp = heredoc_expanding(line, lim);
		(write(1, "> ", 2), write(fd, here_exp, ft_strlen(here_exp)));
		line = (free(line), get_next_line(0));
	}
	close(fd);
	return (name);
}

char	*mark_here_doc(char *str)
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
		if (str[i] == '<' && !flag)
			mark[i] = '2';
		else if (str[i] == 32)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
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
	int		i;
	int		len_her;

	//use the reform_redirection(line) here
	//the convert **p to a str , and asing it to *line
	i = 0;
	if (!*line)
		return ;
	mark = mark_here_doc(*line);
	splt = upgrade_split(*line, mark);
	mark = *line;
	len = len_ptr(splt);
	len_her = count_heredoc(splt);
	while (splt[i])
	{
		if (!ft_strcmp(splt[i], "<<") && len_her > 1)
		{
			splt[i] = (free(splt[i]), NULL);
			i++;
			splt[i] = (free(splt[i]), NULL);
			len_her--;
		}
		else if (!ft_strcmp(splt[i], "<<") && len_her == 1)
		{
			i++;
			free(splt[i]);
			splt[i] = name;
			break ;
		}
		i++;
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


char	*open_heredocs(char	**splt, int num_here)//this function will open all the here_docs and will return the last filename_heredoc
{
	// char		**splt;
	// char		*mark;
	char		*heredoc_filname = NULL;
	//int			num_here;
	int			i;

	i = 0;
	// mark = mark_here_doc(line);
	// splt = upgrade_split(line, mark);
	//num_here = count_heredoc(splt);
	// if (num_here > 16)
	// {
	// 	printf("minishell: maximum here-document count exceeded\n");
	// 	exit(2);
	// }
	if (fork() == 0)
	{
		signal(SIGINT, handle_sig);
		while (splt[i])
		{
			if (!ft_strcmp(splt[i], "<<") && num_here > 1)
			{
				her_doc(splt[i + 1], 0);
				num_here--;
			}
			else if (!ft_strcmp(splt[i], "<<") && num_here == 1)
			{
				heredoc_filname = her_doc(splt[i + 1], 1);
				num_here--;
			}
			i++;
		}
	}
	///signal(SIGINT, SIG_IGN);
	wait(NULL);
	return (heredoc_filname);
}

//handle the signal and check the expanding of the here_doc
void	check_here_doc(char **line)
{
	char	*heredoc_filname;
	char	**splt;
	char	*mark;
	int		num_here;

	if (!is_here_needle(*line, "<<"))
		return ;
	mark = mark_here_doc(*line);
	splt = upgrade_split(*line, mark);
	num_here = count_heredoc(splt);
	if (num_here > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		exit(2);
	}
	heredoc_filname = open_heredocs(splt, num_here);
	keep_last_heredoc(line, heredoc_filname);
	//*line = reform_redirection(*line);
	//printf("line:%s, filename:%s\n", *line, (*herdoc).filename);
}


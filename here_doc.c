/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:37 by iantar            #+#    #+#             */
/*   Updated: 2023/04/07 03:04:33 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//about creating a file_heredoc_name, create a function that open a file with a name
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

char	*take_of(char *line)
{
	int	len;
	int	i;

	i = 0;
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (i < len)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return (line);
		}
		i++;
	}
	return (line);
}

//use reform cmd : >> << > < must be the last
void	her_doc(char *lim, int to_save, t_heredoc	*here)
{
	char		*line;
	char		*name;

	lim = remove_quote(lim);
	if (to_save)
	{
		name = heredoc_filename();
		(*here).fd = open(name, O_TRUNC | O_RDWR | O_CREAT, 0666);
		if ((*here).fd == -1)
			return ;
		(*here).filename = name;
	}
	else
	{
		(*here).fd = -1;
		(*here).filename = NULL;
	}
	line = (write(1, "> ", 2), get_next_line(0));
	while (1)
	{
		if (!line)
			return ;
		if (!ft_strcmp(line, lim))
		{
			free(line);
			return ;
		}
		(write(1, "> ", 2), write((*here).fd, heredoc_expanding(line, lim), ft_strlen(line)));
		line = (free(line), get_next_line(0));
	}
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
		if (!ft_strncmp(splt[i], "<<", ft_strlen(splt[i])) && len_her > 1)
		{
			splt[i] = (free(splt[i]), NULL);
			i++;
			splt[i] = (free(splt[i]), NULL);
			len_her--;
		}
		else if (!ft_strncmp(splt[i], "<<", ft_strlen(splt[i])) && len_her == 1)
		{
			i++;
			free(splt[i]);
			splt[i] = name;
			break ;
		}
		i++;
	}
	i = 0;
	free(mark);
	while (!splt[i])
		i++;
	*line = splt[i];
	while (++i < len)
	{
		if (splt[i])
		{
			mark = *line;
			*line = ft_strjoin(*line, splt[i]);
			//splt[i] = NULL;
			free(mark);
		}
	}
	free(splt);
}


t_heredoc	open_heredocs(char *line)//this function will open all the here_docs and will return the last filename_heredoc
{
	t_heredoc	rtn_heredoc;
	char		**splt;
	char		*mark;
	int			num_here;
	int			i;

	i = 0;
	mark = mark_here_doc(line);
	splt = upgrade_split(line, mark);
	num_here = count_heredoc(splt);
	if (num_here > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		exit(2);
	}
	while (splt[i])
	{
		if (!ft_strncmp(splt[i], "<<", ft_strlen(splt[i])) && num_here > 1)
		{
			her_doc(splt[i + 1], 0, &rtn_heredoc);
			num_here--;
		}
		else if (!ft_strncmp(splt[i], "<<", ft_strlen(splt[i]))
			&& num_here == 1)
		{
			her_doc(splt[i + 1], 1, &rtn_heredoc);
			num_here--;
		}
		i++;
	}
	return (rtn_heredoc);
}

//handle the signal and check the expanding of the here_doc
//
void	check_here_doc(char **line, t_heredoc	*herdoc)
{
	if (!is_here_needle(*line, "<<"))
		return ;
	signal(SIGINT, handle_sig);
	*herdoc = open_heredocs(*line);
	keep_last_heredoc(line, (*herdoc).filename);
	//*line = reform_redirection(*line);
	//printf("line:%s, filename:%s\n", *line, (*herdoc).filename);
}


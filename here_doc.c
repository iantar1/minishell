/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:37 by iantar            #+#    #+#             */
/*   Updated: 2023/04/29 17:53:09 by iantar           ###   ########.fr       */
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

	buf = malloc(51);
	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		write(2, "minishell:file can't open\n", 26);
		// modify_var("?", "1");
		return (NULL);
	}
	read(fd, buf, 50);
	close(fd);
	buf[50] = '\0';
	name = malloc(6);
	i = -1;
	j = -1;
	while (buf[++i] && j < 4)
	{
		if (ft_isalnum(buf[i]))
			name[++j] = buf[i];
	}
	free(buf);
	if (j == -1)
	{
		//printf(YEL"NOOOOOOOO\n"REST);
		return (heredoc_filename());
	}
	//printf("WORNING, j=%d\n", j);
	name[++j] = '\0';
	return (name);
}


char	*her_doc(char *lim, int to_save, int fds)
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
		write(fds, name, ft_strlen(name));
		close(fds);
		fd = -1;//just for not creating any files
		fd = open(name, O_TRUNC | O_RDWR | O_CREAT, 0666);
		if (fd == -1)
		{
			//printf("I MUST NOT APPEARE\n");
			free(name);
			write(2, "minishell:file can't open\n", 26);
			// modify_var("?", "1");//you must add 1 to the exit_status
			return (NULL);
		}
	}
	else
	{
		fd = -1;
		name = lim;//becouse NULL is reserved when we can't open a file.
	}
	line = (write(1, "> ", 2), get_next_line(0));
	while (1)
	{
		if (!line)
			return (printf("- - - - - - - -\n"), close(fd), name);
		if (!here_strcmp(line, new_lim))
		{
			printf("* * * * * * * * * * *\n");
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
		else if ((str[i] == '>' || str[i] == ')') && !flag)
			mark[i] = '3';
		else if (str[i] <= SPACE && str[i] >= 0)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

unsigned char	ft_strcmp(const char *s1, const char *s2)
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
			free(mark);
		}
	}
	free(splt);
}


void	handle_sig(int sig)
{
	(void)sig;
	exit(1);
}

char	*open_heredocs(char	**splt, int num_here)//this function will open all the here_docs and will return the last filename_heredoc
{
	char	*heredoc_filname;
	int		i;
	int		pid;
	int		fds[2];
	int		state;

	i = 0;
	if (pipe(fds) == -1)
		return (NULL);
	signal(SIGINT, handle_sig);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		while (splt && splt[i])
		{
			if (!ft_strcmp(splt[i], "<<") && num_here > 1)
			{
				// if (!her_doc(splt[i + 1], 0))
				// 	return (NULL);
				if (!her_doc(splt[i + 1], 0, -1))
					(printf("+ + + + + + + +"), exit(1));
				num_here--;
			}
			else if (!ft_strcmp(splt[i], "<<") && num_here == 1)
			{
				heredoc_filname = her_doc(splt[i + 1], 1, fds[1]);
				if (!heredoc_filname)
					(printf("; ; ; ; ; ; ; ;"), exit(1));
				//write(fds[1], heredoc_filname, ft_strlen(heredoc_filname));
				// if (!heredoc_filname)
				// 	return (NULL);
				printf("*******heredoc_name:%s\n", heredoc_filname);
				num_here--;
			}
			i++;
		}
		//write(fds[1], heredoc_filname, ft_strlen(heredoc_filname));
		close(fds[0]);
		close(fds[1]);
		exit(0);
	}
	//close(fds[0]);
	signal(SIGINT, SIG_IGN);
	close(fds[1]);
	heredoc_filname = malloc(6);
	pid = waitpid(pid, &state, 0);
	i = read(fds[0], heredoc_filname, 6);
	heredoc_filname[5] = '\0';
	close(fds[0]);
	if (i == -1 || !i)
	{
		printf("I AM HERA*************************\n");
		return (NULL);
	}
	if (state)
	{
		printf("PPPP:%s\n", heredoc_filname);
		unlink(heredoc_filname);
		//free(heredoc_filname);
		return (NULL);
	}
	//printf("state:%d\n", state);
	printf("WHY:%s\n", heredoc_filname);
	//printf("herdoc_name:%s\n", heredoc_filname);
	close(fds[0]);
	return (heredoc_filname);
}

//handle the signal and check the expanding of the here_doc
int	check_here_doc(char **line)
{
	char	*heredoc_filname;
	char	**splt;
	char	*mark;
	int		num_here;

	if (!is_here_needle(*line, "<<"))
		return (0);
	mark = mark_here_doc(*line);
	//printf("mark:%s\n", mark);
	splt = upgrade_split(*line, mark);
	num_here = count_heredoc(splt);
	if (num_here > 16)
	{
		printf("minishell: maximum here-document count exceeded\n");
		exit(2);
	}
	//signal(SIGINT, handle_sig);
	heredoc_filname = open_heredocs(splt, num_here);
	if (!heredoc_filname)
		return (1);
	//printf("heredoc_filname:%s\n", heredoc_filname);
	//signal(SIGINT, SIG_IGN);
	if (!heredoc_filname)
		return (1);
	//printf("i must not be here\n");
	keep_last_heredoc(line, heredoc_filname);
	return (0);
}
//ctrl + c : you delete the file that you create, and 

// solution :split with || and &&  and send chuncks to open_herd and save_last_herdoc
// store all herdoc filename in linked list , when you press crl+c unlink them.
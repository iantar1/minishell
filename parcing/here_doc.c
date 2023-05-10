/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:19:37 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 20:16:21 by iantar           ###   ########.fr       */
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

char	*join_evrything(char **splt)//done
{
	char	*rtn_str;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = -1;
	while (splt[++i])
	{
		j = -1;
		while (splt[i] && splt[i][++j])
			len++;
	}
	rtn_str = upgrade_malloc(len + 1, 0);
	len = -1;
	i = 0;
	while (splt[i])
	{
		j = -1;
		while (splt[i] && splt[i][++j])
			rtn_str[++len] = splt[i][j];
		i++;
	}
	rtn_str[++len] = '\0';
	return (rtn_str);
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
		return (free(buf), heredoc_filename());
	name[++ij[1]] = '\0';
	return (free(buf), name);
}
int	sendherdoc_getfd(int to_save, int fds)//if it returns 0 than it's error
{
	char	*name;
	char	*new_name;
	int		fd;

	if (to_save)
	{
		name = heredoc_filename();
		new_name = strjoin_upgrade("/tmp/", name);
		free(name);
		write(fds, new_name, ft_strlen(new_name));
		close(fds);
		fd = open(new_name, O_TRUNC | O_RDWR | O_CREAT, 0666);
		if (fd == -1)
		{
			free(new_name);
			write(2, "minishell:file can't open\n", 26);
			modify_env_var("?", "1");//you must add 1 to the exit_status
			return (0);
		}
	}
	else
		fd = -1;
	return (fd);
}

char	her_doc(char *lim, int to_save, int fds)
{
	char	*line;
	int		fd;
	char	*new_lim;
	char	*here_exp;

	new_lim = remove_quote(lim);
	fd = sendherdoc_getfd(to_save, fds);
	if (!fd)
		return (0);
	line = (write(1, "> ", 2), get_next_line(0));
	while (1)
	{
		if (!line)
			return (close(fd), 1);
		if (!here_strcmp(line, new_lim))
		{
			free(line);
			return (close(fd), 1);
		}
		here_exp = heredoc_expanding(line, lim);
		(write(1, "> ", 2), write(fd, here_exp, ft_strlen(here_exp)));
		line = (free(line), get_next_line(0));
	}
	close(fd);
	return (1);
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
}

void	change_line(char **splt, char **line, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = *line;
	while (!splt[i])
		i++;
	*line = splt[i];
	while (++i < len)
	{
		if (splt[i])
		{
			tmp = *line;
			*line = strjoin_upgrade(*line, " ");
			free(tmp);
			tmp = *line;
			*line = strjoin_upgrade(*line, splt[i]);
			free(tmp);
		}
	}
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
	free(mark);
	len = len_ptr(splt);
	change_fill_splt(splt, name);
	change_line(splt, line, len);
	free(splt);
}

void	handle_sig(int sig)
{
	(void)sig;
	exit(1);
}

void	open_herdoc_next(char	**splt, int *fds, int num_here)
{
	int	i;

	i = 0;
	while (splt && splt[i])
	{
		if (!ft_strcmp(splt[i], "<<") && num_here > 1)
		{
			if (!her_doc(splt[i + 1], 0, -1))
				exit(1);
			num_here--;
		}
		else if (!ft_strcmp(splt[i], "<<") && num_here == 1)
		{
			if (!her_doc(splt[i + 1], 1, fds[1]))
				exit(1);
			num_here--;
		}
		i++;
	}
	close(fds[0]);
	close(fds[1]);
	exit(0);
}

char	*open_heredocs(char	**splt, int num_here)
{
	char	*heredoc_filname;
	int		i;
	int		pid;
	int		fds[2];
	int		state;

	i = 0;
	if (pipe(fds) == -1)
		return (NULL);
	pid = (signal(SIGINT, handle_sig), fork());
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		open_herdoc_next(splt, fds, num_here);
	(signal(SIGINT, SIG_IGN), close(fds[1]));
	heredoc_filname = upgrade_malloc(11, 0);
	pid = waitpid(pid, &state, 0);
	i = read(fds[0], heredoc_filname, 11);
	heredoc_filname[10] = '\0';
	close(fds[0]);
	if (i == -1 || !i)
		return (free(heredoc_filname), NULL);
	if (state)
		return (free(heredoc_filname), modify_env_var("?", "1"), NULL);
	return (heredoc_filname);
}

char	*herdoc_handle(char **splt_oper)
{
	char	*mark;
	char	**splt;
	int		num_here;
	int		i;
	char	*heredoc_filname;

	i = -1;
	while (splt_oper[++i])
	{
		if (!ft_strncmp(splt_oper[i], "|", 1) || !ft_strcmp(splt_oper[i], "&&"))
			continue ;
		mark = mark_here_doc(splt_oper[i]);
		splt = upgrade_split(splt_oper[i], mark);
		num_here = (free(mark), count_heredoc(splt));
		if (!num_here)
			continue ;
		heredoc_filname = open_heredocs(splt, num_here);
		if (!heredoc_filname)
			return (NULL);
		keep_last_heredoc(&splt_oper[i], heredoc_filname);
	}
	return (join_evrything(splt_oper));
}

int	check_here_doc(char **line)
{
	char	**splt;
	char	**splt_oper;
	char	*mark;
	int		num_here;

	if (!is_here_needle(*line, "<<"))
		return (0);
	mark = mark_here_doc(*line);
	splt = upgrade_split(*line, mark);
	num_here = count_heredoc(splt);
	(free_ptr(splt), free(mark));
	if (num_here > 16)
	{
		write(2, "minishell: maximum here-document count exceeded\n", 48);
		exit(2);
	}
	mark = ft_mark_operator(*line, 0);
	splt_oper = upgrade_split(*line, mark);
	free(mark);
	*line = herdoc_handle(splt_oper);
	free_ptr(splt_oper);
	return (0);
}

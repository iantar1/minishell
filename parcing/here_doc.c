/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:19:37 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 14:44:12 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_oi.h"

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
			return (close(fd), 1);
		here_exp = heredoc_expanding(line, lim);
		(write(1, "> ", 2), write(fd, here_exp, ft_strlen(here_exp)));
		line = get_next_line(0);
	}
	close(fd);
	return (1);
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
		return (NULL);
	if (state)
		return (modify_env_var("?", "1"), NULL);
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
		num_here = (count_heredoc(splt));
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
	if (num_here > 16)
	{
		write(2, "minishell: maximum here-document count exceeded\n", 48);
		exit(2);
	}
	mark = ft_mark_operator(*line, 0);
	splt_oper = upgrade_split(*line, mark);
	*line = herdoc_handle(splt_oper);
	return (0);
}

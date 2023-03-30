/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:19:37 by iantar            #+#    #+#             */
/*   Updated: 2023/03/26 18:15:36 by iantar           ###   ########.fr       */
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

//use reform cmd : >> << > < must be the last
void	here_doc(char *lim, int to_save)
{
	char	*line;
	int		fd;

	signal(SIGINT, handle_sig);
	if (to_save)
	{
		fd = open("her_tmp", O_TRUNC | O_RDWR | O_CREAT, 0666);
		if (fd == -1)
			return ;
	}
	else
		fd = -1;
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
		(write(1, "> ", 2), write(fd, line, ft_strlen(line)));
		line = (free(line), get_next_line(0));
	}
}

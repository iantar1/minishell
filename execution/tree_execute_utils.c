/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execute_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:45:38 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/15 14:27:32 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

// int	fix_red(int fd, int *in, int *out)
// {
// 	int	new;

// 	if (!oi_strcmp(ttyname(fd), "stdout"))
// 	{
// 		new = 1;
// 		*out = 1;
// 	}
// 	else if (!oi_strcmp(ttyname(fd), "stdin"))
// 	{
// 		new = 0;
// 		*in = 0;
// 	}
// 	else
// 	{
// 		new = 2;
// 		*out = 2;
// 	}
// 	close(fd);
// 	return (new);
// }

static int	redirect_handle(t_tree *tree, int *in, int *out)
{
	int	fd;

	fd = -1;
	if (tree->ambiguous)
		return (ft_dprintf(2, "ambiguous redirect\n"), sv_exit(1), -2);
	else if (tree->data.type == IN || tree->data.type == HERE_DOC)
	{
		fd = open(tree->right_c->data.cmd, O_RDONLY);
		if (fd != -1 && !isatty(fd))
			*in = fd;
	}
	else if (tree->data.type == OUT || tree->data.type == APPEND)
	{
		if (tree->data.type == APPEND)
			fd = open(tree->right_c->data.cmd, 0x209, 0666);
		else
			fd = open(tree->right_c->data.cmd, 0x601, 0666);
		if (fd != -1 && !isatty(fd))
			*out = fd;
	}
	return (fd);
}

int	pipes(t_tree *tree, int in, int out)
{
	int	fds[2];
	int	pid;
	int	st;

	if (pipe(fds))
		return (perror("PIPE"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("FORK FAILED"), 1);
	if (!pid)
	{
		close(fds[0]);
		st = subshell(tree->left_c, in, fds[1], tree->child_level);
		close(fds[1]);
		exit(st);
	}
	close(fds[1]);
	st = subshell(tree->right_c, fds[0], out, tree->child_level);
	close(fds[0]);
	waitpid(pid, NULL, 0);
	sv_exit(st);
	return (st);
}

int	redirect_io_file(t_tree *tree, int in, int out)
{
	int	fd;
	int	status;

	if (!tree)
		return (0);
	status = 0;
	fd = redirect_handle(tree, &in, &out);
	if (fd == -2)
		return (-2);
	if (fd == -1 && tree->data.type == IN && errno != 13)
		return (ft_dprintf(2, "%s : No such file or directory\n"
				, tree->right_c->data.cmd), sv_exit(1));
	else if ((fd == -1 && (tree->data.type == OUT
				|| tree->data.type == APPEND)) && errno == 13)
		return (ft_dprintf(2, "%s : Permission denied\n"
				, tree->right_c->data.cmd), sv_exit(1));
	else if (fd == -1)
		return (ft_dprintf(2, "%s : No such file or directory\n"
				, tree->right_c->data.cmd), sv_exit(1));
	status = subshell(tree->left_c, in, out, tree->child_level);
	if (fd != 0 && fd != 1 && fd != 2)
		close(fd);
	return (status);
}

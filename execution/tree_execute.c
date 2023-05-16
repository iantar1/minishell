/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:51:29 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/14 17:24:18 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"
// last version in 2023-04-03 2h:01min handling
// ambiguous redirection ("message only")

// int	wait_for(int *st, int pid2)
// {
// 	int	pid;

// 	pid = sv_pid(-1);
// 	if (pid2)
// 		pid = pid2;
// 	waitpid(pid, st, 0);
// 	sv_exit(*st);
// 	while (!waitpid(-1, NULL, 0))
// 		;
// 	return (pid);
// }

int	subshell(t_tree *tree, int in, int out, int level)
{
	int	st;
	int	pid;

	if (!tree)
		return (0);
	if (level == tree->child_level)
		return (exec_tree(tree, in, out));
	pid = fork();
	if (pid == -1)
		return (perror("FORK FAILED"), 1);
	signal(SIGINT, SIG_IGN);
	if (!pid)
		exit(exec_tree(tree, in, out));
	waitpid(pid, &st, 0);
	return (sv_exit(st));
}

// function needs to be tested 
int	exec_tree(t_tree *tree, int in, int out)
{
	int	status;

	status = 0;
	if (!tree || !tree->data.cmd)
		return (0);
	if (tree->data.type == COMMAND || !tree->data.cmd[0])
		return (sv_exit(_execute(tree, in, out)));
	if (tree->data.type == PIPE)
		return (pipes(tree, in, out));
	if (tree->data.cmd && tree->data.type != AND && tree->data.type != OR)
		return (redirect_io_file(tree, in, out));
	status = subshell(tree->left_c, in, out, tree->child_level);
	if ((tree->data.type == AND && !status)
		|| (tree->data.type == OR && status))
		status = subshell(tree->right_c, in, out, tree->child_level);
	sv_exit(status);
	return (status);
}

int	complete_exec(t_tree *tree, int in, int out, char *paths)
{	
	char	*full_path;
	int		status;

	(signal(SIGQUIT, SIG_DFL), signal(SIGINT, SIG_DFL));
	(dup2(in, 0), (in != 0) && close (in));
	(dup2(out, 1), (out != 1) && close(out));
	if (is_builtin(tree->data.cmd))
		return (exit(handle_cmd(tree, out)), 1);
	full_path = get_path(tree->data.cmd, paths, 0);
	if (!full_path)
		return (free(paths), print_exec_errors(full_path, tree->data.cmd, 5)
			, free(full_path), exit(sv_exit(127)), 127);
	if (execve(full_path, tree->data.args, from_list_to_char(0)) == -1)
	{
		status = print_exec_errors(full_path, tree->data.cmd, 1);
		free(full_path);
		(free(paths), exit(sv_exit(status)));
	}
	return (1);
}

/// @brief 
/// @param tree 
/// @param in 
/// @param out 
/// @return exit status
int	_execute(t_tree *tree, int in, int out)
{
	char	*paths;
	int		st;
	int		pid;
	char	*sv_path;

	st = 0;
	if (is_builtin(tree->data.cmd)
		&& ((tree->parent && tree->parent->data.type != PIPE) || !tree->parent))
		return (handle_cmd(tree, out));
	paths = get_env_line("PATH");
	pid = fork();
	if (pid == -1)
		return ((paths && (paths = (free(paths), NULL)))
			, perror("FORK FAILED"), 1);
	if (!pid)
		complete_exec(tree, in, out, paths);
	(signal(SIGINT, &handle), signal(SIGQUIT, &handle));
	(waitpid(pid, &st, 0), sv_exit(st));
	(signal(2, sig_handler), signal(3, SIG_IGN));
	sv_path = get_path(tree->data.cmd, paths, 0);
	(!st && modify_env_var("_", sv_path));
	(sv_path && (free(sv_path), 0));
	if (paths)
		paths = (free(paths), NULL);
	return (sv_exit(st + 128));
}

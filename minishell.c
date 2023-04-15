/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:21 by iantar            #+#    #+#             */
/*   Updated: 2023/04/15 10:53:29 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"


// int	_execute(t_tree *tree);

// int	is_valid(t_tree *tree, int st)
// {
// 	return ((tree->data.type == OR && st) || (tree->data.type == AND
// 			&& !st) || tree->data.type == PIPE);
// }

// int	handle_case(t_tree *tree, int *read_end, int fds[2])
// {
// 	int	fd;

// 	fd = -1;
// 	if (tree->data.type == PIPE)
// 	{
// 		if (pipe(fds))
// 			return (dprintf(2, "PIPE FAILED\n"), -2);
// 		(dup2(fds[1], 1), close(fds[1]));
// 	}
// 	if (tree->amniguous)
// 		return (dprintf(2, "ambiguous redirect\n"), -2);
// 	if (tree->data.type == IN)
// 	{
// 		fd = open(tree->right_c->data.cmd, O_RDONLY);
// 		(fd != -1) && dup2(fd, 0);
// 	}
// 	else if (tree->data.type == OUT || tree->data.type == APPEND)
// 	{
// 		if (tree->data.type == APPEND)
// 			fd = open(tree->right_c->data.cmd, 0x209, 0666);
// 		else
// 			fd = open(tree->right_c->data.cmd, 0x601, 0666);
// 		(fd != -1) && dup2(fd, 1);
// 	}
// 	return (*read_end = fds[0], fd);
// }

// int	exec_tree(t_tree *tree, int in, int out, int level)
// {
// 	int	st;
// 	int	read_end;
// 	int	fd;
// 	int	fds[2];

// 	st = 0;
// 	// if ()
// 	if (tree && tree->data.type != -1 && tree->data.cmd)
// 	{
// 		fd = handle_case(tree, &read_end, fds);
// 		if (fd != -2)
// 			st = exec_tree(tree->left_c, in, out, level + 1);
// 		(tree->data.type == AND || tree->data.type == OR) && wait(&st);
// 		if (tree->data.type == PIPE)
// 			(dup2(out, 1), (dup2(read_end, 0), close(read_end)));
// 		if (is_valid(tree, st))
// 			st = exec_tree(tree->right_c, in, out, level + 1);
// 		(tree->data.type == OUT || tree->data.type == APPEND
// 			|| tree->data.type == IN) && (close(fd));
// 	}
// 	else if (tree && tree->data.cmd)
// 		st = _execute(tree);
// 	return (st);
// }

// //the null need to be filled

// int	_execute(t_tree *tree)
// {
// 	int		status;
// 	char	**env_char;

// 	env_char = NULL;
// 	// env_char = from_list_to_char();
// 	status = 0;
// 	if (!fork())
// 		(execve(tree->data.cmd, tree->data.args, env_char)
// 			, (perror(tree->data.cmd), exit(127)));
// 	 if (tree->parent && (tree->parent->data.type == OR
// 	 		|| tree->parent->data.type == AND))
// 		wait(&status);
// 	return (status);
// }

void	print_args(char **args)
{
	int	i;

	i = -1;
	printf(" ->args: {");
	while (args[++i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(", ");
	}
	printf("}");
	printf("\n");
}

void	print_tree(t_tree *tree)
{
	printf(BBLU"CMD: "REST);
	printf(BGRN"%s\n"REST, tree->data.cmd);
	printf(" ->child_level:%d\n", tree->child_level);
	printf(" ->type:%d\n", tree->data.type);
	printf(YEL" ->ambiguous :%d\n"REST, tree->amniguous);
	//printf(" ->heredoc_filename:%s\n", tree->my_here_doc.filename);
	print_args(tree->data.args);
	if ((tree->left_c))
		print_tree(tree->left_c);
		//return ;
	if ((tree->right_c))
		print_tree(tree->right_c);
		//return ;
}

int	main(int ac, char *av[], char **env)
{
	char	*line;
	t_tree	*tree;
	//char	*tmp;
	//char	*mark;
	//char	**buf;

	((void)av, (void)ac);
	g_env = new_line("var=a     b");
	g_env->next = create_env(env);
	_free_ = ft_lstnew("START");
	while (1)
	{
		line = readline("minishell$ "BRED);
		if (!line)
			return ((write(1, "\n", 1)), 0);
		add_history(line);
		//tmp = ft_strdup(line);
		if (syntax_error(line))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			continue ;
		}
		remove_surrounded_sp(&line);
		check_here_doc(&line);
		if (!line)
			continue ;
		tree = ft_tree_new(&line, NULL, 0);
		parse_tree(&line, tree, "root");
		print_tree(tree);

		// int	in;
		// int	out;

		// in = dup(0);
		// out = dup(1);
		// exec_tree(tree, in, out, 0);
		// ((dup2(in, 0), dup2(out, 1)), (close(in), close(out)));
		// while (!wait(NULL))
		// 	;
	}
	return (0);
}

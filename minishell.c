/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:21 by iantar            #+#    #+#             */
/*   Updated: 2023/04/05 02:13:10 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"

// t_tree	*ft_tree_new(void *content, t_tree *parent)
// {
// 	t_tree	*ptr;

// 	ptr = (t_tree *)malloc(sizeof(t_tree));
// 	if (!ptr)
// 		return (0);
// 	ptr->content = content;
// 	ptr->right_child = NULL;
// 	ptr->left_child = NULL;
// 	ptr->parent = parent;
// 	return (ptr);
// }

// <void	handle_sig(int sig)
// {
// 	//(void)sig;
// 	printf("sig:%d\n", sig);
// 	exit(0);
// 	return ;
// }>

void	show_result(char **buf, t_env *env_no)
{
	int	i;

	i = -1;
	printf(" -------------\n");
	(void)env_no;
	while (buf[++i])
	{
		if (!closed_quote(buf[i]))
			printf("syntax error\n");
		else
		{
			printf("%s ", remove_quote(ft_expand(buf[i])));
			//printf("%s\n", get_value(char *key, int len));
			// if (need_expand(buf[i]))
			// 	expand(&buf, env_no);
			// else if (closed_quote(buf[i]))
			//printf("cmd:%s\n", remove_quote(buf[i]));
			//printf("%s ", buf[i]);
			// if (!ft_strncmp("<<", buf[i], 2))
			// {
			// 	if (fork() == 0)
			// 	{
			// 		here_doc("lim\n", 1);
			// 		//signal(SIGINT, handle_sig);
			// 	}
			// 	signal(SIGINT, SIG_IGN);
			// 	wait(NULL);
			// }
		}
	}
	printf("\n -------------\n");
}

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
	printf("CMD: %s\n", tree->data.cmd);
	print_args(tree->data.args);
	printf(" ->child_level:%d\n", tree->child_level);
	if (!(tree->left_c))
		return ;
	if (!(tree->right_c))
		return ;
	print_tree(tree->left_c);
	print_tree(tree->right_c);
}

int	main(int ac, char *av[], char **env)
{
	char	*line;
	t_tree	*tree;
	//char	*mark;
	//char	**buf;

	((void)av, (void)ac);
	g_env = new_line("?=0");
	g_env->next = create_env(env);
	//printf("%s\n", ft_expand("hello$PATH"));
	//signal(SIGINT, handle_sig);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return ((write(1, "\n", 1)), 0);
		add_history(line);
		remove_surrounded_sp(&line);
		if (!line)
			continue ;
		// printf("child_levl:%d\n", remove_first_parenthisis(&line));
		// printf("line:%s****\n", line);
		tree = ft_tree_new(&line, NULL, 0);
		parse_tree(line, tree, "root");
		print_tree(tree);
		// if (closed_parenthesis(line) && !emty_parenthesis(line))
		// 	printf("YES\n");
		// else
		// 	printf("minishell: syntax error\n");
		//mark = mark_first_parenthisis(line);
		// if (!valid_operators(mark))
		// 	printf("minishell: syntax error\n");
		//buf = upgrade_split(line, mark);
		//buf = reform_redirection(line);
		//printf("mark:      %p\n", buf);
		// buf = reform_redirection(line);
		// show_result(buf, g_env);
		//if (buf[0])
	}
	return (0);
}

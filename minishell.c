/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:21 by iantar            #+#    #+#             */
/*   Updated: 2023/04/13 02:33:32 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"

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
	printf(" ->child_level:%d\n", tree->child_level);
	printf(" ->type:%d\n", tree->data.type);
	printf(" ->ambiguous :%d\n", tree->amniguous);
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
	g_env = new_line("?=0");
	g_env->next = create_env(env);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return ((write(1, "\n", 1)), 0);
		add_history(line);
		//tmp = ft_strdup(line);
		if (syntax_error(line))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			if (fork() == 0)
				exit(258);
			wait(NULL);
			continue ;
		}
		printf("line:%s\n", line);
		remove_surrounded_sp(&line);
		printf("line:%s\n", line);
		if (!line)
			continue ;
		tree = ft_tree_new(&line, NULL, 0);
		parse_tree(&line, tree, "root");
		print_tree(tree);
	}
	return (0);
}

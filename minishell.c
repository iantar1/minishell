/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:21 by iantar            #+#    #+#             */
/*   Updated: 2023/04/09 01:28:32 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"

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
			printf(", .");
	}
	printf("}");
	printf("\n");
}

void	print_tree(t_tree *tree)
{
	printf("CMD: %s\n", tree->data.cmd);
	printf(" ->child_level:%d\n", tree->child_level);
	printf(" ->type:%d\n", tree->data.type);
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
	//char	*mark;
	//char	**buf;

	((void)av, (void)ac);
	//g_env = new_line("?=0");
	g_env = new_line("var=a     ");
	g_env->next = create_env(env);
	//printf("%s\n", ft_expand("hello$PATH"));
	//signal(SIGINT, handle_sig);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return ((write(1, "\n", 1)), 0);
		add_history(line);
		if (amniguous_redirect(line))
		{
			printf("AMNBIGUOUS\n");
			continue ;
		}
		remove_surrounded_sp(&line);
		if (!line)
			continue ;
		tree = ft_tree_new(&line, NULL, 0);
		//set_null_lkolxi(tree);
		parse_tree(&line, tree, "root");
		print_tree(tree);
	}
	return (0);
}

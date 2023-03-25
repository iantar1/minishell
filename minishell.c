/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:21 by iantar            #+#    #+#             */
/*   Updated: 2023/03/25 14:45:39 by iantar           ###   ########.fr       */
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
			//printf("result:%s\n", remove_quote(ft_expand(buf[i])));
			//printf("%s\n", get_value(char *key, int len));
			// if (need_expand(buf[i]))
			// 	expand(&buf, env_no);
			// else if (closed_quote(buf[i]))
			//printf("cmd:%s\n", remove_quote(buf[i]));
			printf("%s ", buf[i]);
		}
	}
	printf("\n -------------\n");
}

int	main(int ac, char *av[], char **env)
{
	char	*line;
	char	*mark;
	char	**buf;

	((void)av, (void)ac);
	g_env = new_line("?=0");
	g_env->next = create_env(env);
	//printf("%s\n", ft_expand("hello$PATH"));
	here_doc("lim\n", 0);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return ((write(1, "\n", 1)), 0);
		// if (closed_parenthesis(line) && !emty_parenthesis(line))
		// 	printf("YES\n");
		// else
		// 	printf("minishell: syntax error\n");
		mark = mark_first_parenthisis(line);
		// if (!valid_operators(mark))
		// 	printf("minishell: syntax error\n");
		//buf = upgrade_split(line, mark);
		buf = reform_redirection(line);
		//printf("mark:      %p\n", buf);
		show_result(buf, g_env);
		if (buf[0])
			add_history(line);
	}
	return (0);
}

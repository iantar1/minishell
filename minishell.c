/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:21 by iantar            #+#    #+#             */
/*   Updated: 2023/03/11 11:38:53 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"

t_tree	*ft_tree_new(void *content, t_tree *parent)
{
	t_tree	*ptr;

	ptr = (t_tree *)malloc(sizeof(t_tree));
	if (!ptr)
		return (0);
	ptr->content = content;
	ptr->right_child = NULL;
	ptr->left_child = NULL;
	ptr->parent = parent;
	return (ptr);
}

void	show_result(char **buf, t_env *env_no)
{
	int	i;

	i = -1;
	printf(" -------------\n");
	(void)env_no;
	while (buf[++i])
	{
		printf("%s\n", buf[i]);
		// if (!closed_quote(buf[i]))
		// 	printf("syntax error\n");
		// else
		// {
		// 	// if (need_expand(buf[i]))
		// 	// 	expand(&buf, env_no);
		// 	// else if (closed_quote(buf[i]))
		// 	// 	printf("cmd:%s\n", remove_quote(buf[i]));
		// }
	}
	printf(" -------------\n");
}

int	main(int ac, char *av[], char **env)
{
	char	*line;
	char	*mark;
	char	**buf;
	t_env	*env_no;

	((void)av, (void)ac);
	env_no = create_env(env);
	while (1)
	{
		line = readline("minishell>");
		if (!line)
			return ((write(1, "\n", 1)), 0);
		//mark = ft_mark(line);
		mark = expand_mark(line);
		buf = upgrade_split(line, mark);
		printf("	  %s\n", mark);
		//show_result(buf, env_no);
		if (buf[0])
			add_history(line);
		free(mark);
	}
	return (0);
}

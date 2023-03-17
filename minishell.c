/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:21 by iantar            #+#    #+#             */
/*   Updated: 2023/03/17 16:59:48 by iantar           ###   ########.fr       */
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
			printf("%s\n", buf[i]);
		}
	}
	printf(" -------------\n");
}

char	*ft_mark1(char *str)
{
	int		i;
	char	*mark;
	char	check;

	if (!str)
		return (NULL);
	mark = malloc(sizeof(char) * ft_strlen(str) + 1);
	check = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 ||  str[i] == 39)
		{
			if (str[i] == check)
				check = 0;
			else if (!check)
				check = str[i];
		}
		if (!check && str[i] == '(')
			check = str[i];
		if (check == '(' && str[i] == ')')
			check = 0;
		if ((str[i] == '|' || str[i] == '&') && !check)
			mark[i] = '2';
		else
			mark[i] = '0';
	}
	mark[i] = '\0';
	return (mark);
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
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return ((write(1, "\n", 1)), 0);
		// if (closed_parenthesis(line) && !emty_parenthesis(line))
		// 	printf("YES\n");
		// else
		// 	printf("minishell: syntax error\n");
		mark = ft_mark1(line);
		// if (!valid_operators(mark))
		// 	printf("minishell: syntax error\n");
		buf = upgrade_split(line, mark);
		//printf("	  %s\n", mark);
		show_result(buf, g_env);
		if (buf[0])
			add_history(line);
	}
	return (0);
}

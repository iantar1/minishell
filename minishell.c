/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:21 by iantar            #+#    #+#             */
/*   Updated: 2023/03/21 12:19:04 by iantar           ###   ########.fr       */
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

char	**mark_first_parenthisis(char *str)//to remove the first parenthesis.(ls | cat > out (cat out | wc)) -> ls | cat > out (cat out | wc)
{
	int		check;
	int		i;
	char	*mark;

	mark = malloc(sizeof(char) * (ft_strlen(str) - 1));
	i = 0;
	check = 0;
	while (str[i])
	{
		if ((str[i] <= 32 || str[i] == '(') && !check)
		{
			mark[i] = '2';
			if (str[i] == '(')
				check++;
		}
		else if (str[i] == ')' && check == 1)
			mark[i] = '2';
		else
			mark[i] = '0';
		i++;
		
	}
	mark[i] = '\0';
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
		mark = mark_logic_operator(ft_mark1(line));
		// if (!valid_operators(mark))
		// 	printf("minishell: syntax error\n");
		buf = upgrade_split(line, mark);
		printf("mark:      %s\n", mark);
		//show_result(buf, g_env);
		if (buf[0])
			add_history(line);
	}
	return (0);
}

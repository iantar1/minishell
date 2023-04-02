/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:17:15 by iantar            #+#    #+#             */
/*   Updated: 2023/04/02 03:05:51 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_ptr(char **ptr)
{
	int	len;

	len = 0;
	while (ptr[len])
		len++;
	return (len);
}

int	ft_type(char *cmd)
{
	if (!cmd)//you need an information to know if cmd a file.
		return (_FILE);
	else if (!ft_strncmp(cmd, ">", ft_strlen(cmd)))
		return (OUT);
	else if (!ft_strncmp(cmd, ">>", ft_strlen(cmd)))
		return (APPEND);
	else if (!ft_strncmp(cmd, "<", ft_strlen(cmd)))
		return (IN);
	else if (!ft_strncmp(cmd, "<<", ft_strlen(cmd)))
		return (HERE_DOC);
	else if (!ft_strncmp(cmd, "|", ft_strlen(cmd)))
		return (PIPE);
	else if (!ft_strncmp(cmd, "||", ft_strlen(cmd)))
		return (OR);
	else if (!ft_strncmp(cmd, "&&", ft_strlen(cmd)))
		return (AND);
	else
		return (COMMAND);
}

t_data	ft_data_new(char *cmd_line)
{
	t_data	data;
	char	**splt;

	splt = ft_split(cmd_line, SPACE);
	data.cmd = splt[0];
	data.args = splt;
	data.type = ft_type(splt[0]);
	return (data);
}

t_tree	*ft_tree_new(char *cmd_line, t_tree *parent_add, int ch_level)
{
	t_tree	*new_tree;

	new_tree = malloc(sizeof(t_tree));
	new_tree->data = ft_data_new(cmd_line);
	new_tree->parent = parent_add;
	new_tree->child_level = ch_level;
	return (new_tree);
}

// void	print_args(char **args)
// {
// 	int	i;

// 	i = -1;
// 	printf("args: {");
// 	while (args[++i])
// 		printf("%s ", args[i]);
// 	printf("}\n");
// }

// void	print_tree(t_tree *tree)
// {
// 	printf("cmd:%s ", tree->data.cmd);
// 	print_args(tree->data.args);
// 	if (tree->left_c)
// 	{
// 		tree = tree->left_c;
// 		print_tree(tree);
// 	}
// 	else if (tree->right_c)
// 	{
// 		tree = tree->right_c;
// 		print_tree(tree);
// 	}
// 	else
// 		return ;
// }

int	need_split(char *mark)
{
	int	i;

	i = -1;
	while (mark[++i])
		if (mark[i] != '0')
			return (1);
	return (0);
}

// t_tree	*parce_tree(char *line, t_tree *tree)
// {
// 	char	*mark;
// 	char	**splt_oper;
// 	int		i;

// 	mark = ft_mark_operator(line);
// 	mark_the_mark_operator(mark);
// 	if (need_split(mark))
// 	{
// 		splt_oper = upgrade_split(line, mark);
// 		tree->data =  
// 		parce_tree(splt_oper[0], tree->left_c);
// 		parce_tree(splt_oper[2], tree->right_c);
// 	}
// 	// i = 0;
// 	// tree->left_c = ft_tree_new(splt_oper[0], tree, 0);
// 	// tree->right_c = ft_tree_new(splt_oper[2], tree, 0);
// 	// print_tree(tree);
// 	return (NULL);
// }

// Read a data in x.
// Allocate memory for a new node and store the address in pointer p.
// Store the data x in the node p.
// Recursively create the left subtree of p and make it the left child of p.
// Recursively create the right subtree of p and make it the right child of p.

void	parse_tree(char *line, t_tree *tree)
{
	char	*mark;
	char	**splt_oper;

	mark = ft_mark_operator(line);
	mark_the_mark_operator(mark);
	splt_oper = upgrade_split(line, mark);
	if (need_split(mark))
	{
		tree->left_c = ft_tree_new(splt_oper[0], tree, 0);
		tree->right_c = ft_tree_new(splt_oper[2], tree, 0);
		tree->data = ft_data_new(splt_oper[1]);
		parse_tree(splt_oper[0], tree->left_c);
		parse_tree(splt_oper[2], tree->right_c);
	}
	else
	{
		tree->left_c = NULL;
		tree->right_c = NULL;
	}
	return ;
}
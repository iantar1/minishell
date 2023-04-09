/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:17:15 by iantar            #+#    #+#             */
/*   Updated: 2023/04/07 08:32:49 by iantar           ###   ########.fr       */
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

int	ft_type(char *cmd)//for FILE_ ane COMMAND, check the parent > or < or >>
{
	if (!ft_strncmp(cmd, ">", ft_strlen(cmd)))
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
		return (-1);
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

int	need_split(char *mark)
{
	int		i;
	char	c;

	i = 0;
	c = mark[i];
	while (mark[++i])
		if (mark[i] != c)
			return (1);
	return (0);
}

t_tree	*ft_tree_new(char **line, t_tree *parent_add, int child_level)
{
	t_tree	*new_tree;

	new_tree = malloc(sizeof(t_tree));
	new_tree->child_level = remove_first_parenthisis(line) + child_level;
	new_tree->data = ft_data_new(*line);
	new_tree->parent = parent_add;
	new_tree->left_c = NULL;
	new_tree->right_c = NULL;
	//new_tree->my_here_doc.filename = NULL;
	//new_tree->my_here_doc.fd = -1;
	return (new_tree);
}

void	parse_tree(char **line, t_tree *tree, char *str)
{
	char	*mark;
	char	**splt_oper;

	// mark = mark_sp_border(line);
	// splt_oper = upgrade_split(line, mark);
	// line = splt_oper[0];
	// free(splt_oper[1]);
	if (!line || !*line || !**line)
		return ;
	mark = ft_mark_operator(*line);
	mark_the_mark_operator(mark);
	splt_oper = upgrade_split(*line, mark);
	//&& ||
	if (need_split(mark))
	{
		tree->left_c = ft_tree_new(&splt_oper[0], tree, tree->child_level);
		tree->right_c = ft_tree_new(&splt_oper[2], tree, tree->child_level);
		tree->data = ft_data_new(splt_oper[1]);
		parse_tree(&splt_oper[0], tree->left_c, "left");
		parse_tree(&splt_oper[2], tree->right_c, "right");
	}
	else
	{
		mark = ft_mark_operator(*line);
		splt_oper = upgrade_split(*line, mark);
		// | 
		if (need_split(mark))
		{
			tree->left_c = ft_tree_new(&splt_oper[0], tree, tree->child_level);
			tree->right_c = ft_tree_new(&splt_oper[2], tree, tree->child_level);
			tree->data = ft_data_new(splt_oper[1]);
			parse_tree(&splt_oper[0], tree->left_c, "left");
			parse_tree(&splt_oper[2], tree->right_c, "right");
		}
		else if (*line)
		{
			//here you wille handle the here_doc
			printf("line_before refore:%s\n", *line);
			*line = reform_redirection(*line);
			printf("line_after reforme:%s\n", *line);
			check_here_doc(line);
			printf("line aftre here_doc:%s\n", *line);
			mark = mark_redirection(*line, 0);
			printf("mark:%s\n", mark);
			splt_oper = upgrade_split(*line, mark);
			// >> << > <
			if (need_split(mark) && len_ptr(splt_oper) > 2)
			{
				tree->left_c = ft_tree_new(&splt_oper[0], tree, tree->child_level);
				tree->right_c = ft_tree_new(&splt_oper[2], tree, tree->child_level);
				tree->data = ft_data_new(splt_oper[1]);
				parse_tree(&splt_oper[0], tree->left_c, "left");
				parse_tree(&splt_oper[2], tree->right_c, "right");
			}
			else if (len_ptr(splt_oper) == 2)
			{
				tree->data = ft_data_new(splt_oper[0]);
				tree->right_c = ft_tree_new(&splt_oper[1], tree, tree->child_level);
				//parse_tree(NULL, NULL, "left");
				parse_tree(&splt_oper[1], tree->right_c, "right");
			}
		}
	}
	return ;
	(void)str;
}

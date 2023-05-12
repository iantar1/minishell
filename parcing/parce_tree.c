/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:17:15 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 23:10:19 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_oi.h"

t_data	ft_data_new(char *cmd_line)
{
	t_data	data;
	char	**splt;
	char	*mark;

	wirldcard_expanding(&cmd_line);
	mark = ft_mark(cmd_line);
	splt = upgrade_split(cmd_line, mark);
	splt = get_last_split(splt);
	if (!splt)
	{
		data.cmd = NULL;
		data.args = NULL;
		data.type = -1;
	}
	else
	{
		data.cmd = unreform_quote(remove_quote(ft_expand(splt[0])));
		data.args = expand_args(splt);
		data.type = ft_type(splt[0]);
	}
	return (data);
}

t_tree	*ft_tree_new(char **line, t_tree *parent_add, int child_level)
{
	t_tree	*new_tree;

	new_tree = upgrade_malloc(sizeof(t_tree), 0);
	new_tree->child_level = remove_first_parenthisis(line) + child_level;
	new_tree->data = ft_data_new(*line);
	new_tree->parent = parent_add;
	new_tree->left_c = NULL;
	new_tree->right_c = NULL;
	new_tree->ambiguous = 0;
	return (new_tree);
}

void	call_fill_nodes(char **splt_oper, t_tree *tree, char check)
{
	tree->left_c = ft_tree_new(&splt_oper[0], tree, tree->child_level);
	tree->right_c = ft_tree_new(&splt_oper[2], tree, tree->child_level);
	tree->data = ft_data_new(splt_oper[1]);
	parse_tree(&splt_oper[0], tree->left_c, check);
	parse_tree(&splt_oper[2], tree->right_c, check);
}

void	red_parce(char **line, t_tree *tree, char check)
{
	char	*mark;
	char	**splt_oper;

	*line = reform_redirection(*line);
	tree->ambiguous = ambiguous_redirect(*line);
	if (check)
		*line = check_swap_red(*line);
	mark = mark_redirection(*line, 0);
	mark_the_red_mark(mark);
	splt_oper = upgrade_split(*line, mark);
	if (need_split(mark) && len_ptr(splt_oper) > 2)
		call_fill_nodes(splt_oper, tree, 0);
	else if (len_ptr(splt_oper) == 2)
	{
		tree->data = ft_data_new(splt_oper[0]);
		tree->right_c = ft_tree_new(&splt_oper[1], tree, tree->child_level);
		parse_tree(&splt_oper[1], tree->right_c, 0);
	}
}

void	parse_tree(char **line, t_tree *tree, char check)
{
	char	*mark;
	char	**splt_oper;

	if (!line || !*line || !**line)
		return ;
	mark = ft_mark_operator(*line, 0);
	mark_the_mark_operator(mark);
	splt_oper = upgrade_split(*line, mark);
	if (need_split(mark))
		call_fill_nodes(splt_oper, tree, 1);
	else
	{
		mark = ft_mark_operator(*line, 0);
		mark_the_pipe_mark(mark);
		splt_oper = upgrade_split(*line, mark);
		if (need_split(mark))
			call_fill_nodes(splt_oper, tree, 1);
		else if (*line)
			red_parce(line, tree, check);
	}
	return ;
}

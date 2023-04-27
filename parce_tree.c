/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:17:15 by iantar            #+#    #+#             */
/*   Updated: 2023/04/27 10:29:08 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_ptr(char **ptr)
{
	int	len;

	len = 0;
	while (ptr && ptr[len])
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

char	**expand_args(char **splt)
{
	int		i;

	i = 0;
	while (splt && splt[i])
	{
		splt[i] = remove_quote(ft_expand(splt[i]));
		i++;
	}
	return (splt);
}

t_data	ft_data_new(char *cmd_line)
{
	t_data	data;
	char	**splt;
	char	*mark;

	wirldcard_expanding(&cmd_line);
	//printf("cmd_line:%s\n", cmd_line);
	mark = ft_mark(cmd_line);
	//printf("ft_mark:%s\n", mark);
	//splt = ft_split(cmd_line, SPACE);
	splt = upgrade_split(cmd_line, mark);
	//printf("@@@:line: %s, aplt[0]:%s\n", cmd_line, splt[0]);
	data.cmd = remove_quote(ft_expand(splt[0]));
	data.args = expand_args(splt);
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

void	mark_the_pipe_mark(char *mark)
{
	int	len;
	int	check;

	len = ft_strlen(mark);
	check = 1;
	while (--len >= 0)
	{
		if (mark[len] == '2' && check)
			check = 0;
		else if (mark[len] == '2')
			mark[len] = '0';
	}
}

void	mark_the_red_mark(char *mark)
{
	int	len;
	int	check;

	len = ft_strlen(mark);
	check = 1;
	while (--len >= 0)
	{
		if (mark[len] == '2' && check)
		{
			check = 0;
			if (len && mark[len - 1] == '2')
				len--;
		}
		else if (mark[len] == '2')
			mark[len] = '0';
	}
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
	new_tree->amniguous = 0;
	return (new_tree);
}

void	parse_tree(char **line, t_tree *tree, char *str)
{
	char	*mark;
	char	**splt_oper;

	if (!line || !*line || !**line)
		return ;
	//tree->child_level = remove_first_parenthisis(line);
	mark = ft_mark_operator(*line, 0);
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
		mark = ft_mark_operator(*line, 0);
		mark_the_pipe_mark(mark);
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
			*line = reform_redirection(*line);
			tree->amniguous = amniguous_redirect(*line);
			keep_last_redir(line);
			mark = mark_redirection(*line, 0);
			//printf("befor_mark:%s\n", *line);
			//printf("afetr_mark:%s\n", mark);
			mark_the_red_mark(mark);
			splt_oper = upgrade_split(*line, mark);
			// >> << > <
			//printf(BGRN"##########\n"REST);
			if (need_split(mark) && len_ptr(splt_oper) > 2)
			{
				//printf("my_line:%s\n", *line);
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
		//printf("line_ino:%s\n", *line);
	}
	return ;
	(void)str;
}

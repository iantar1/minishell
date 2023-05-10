/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 01:17:15 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 16:57:39 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/minishell_oi.h"

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

/// @brief the function handles the allocation and freeing 
///			the old double arrays already
/// @param arr1 
/// @param arr2 
/// @return the joined double array
char	**join_double_array(char **arr1, char **arr2)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	**joined;

	if (!arr1)
		return (arr2);
	if (!arr2)
		return (arr1);
	i = len_double_char(arr1);
	j = len_double_char(arr2);
	k = 0;
	l = 0;
	joined = upgrade_malloc((i + j + 1) * sizeof(char *), 0);
	while (arr1[l])
		joined[k++] = arr1[l++];
	l = 0;
	while (arr2[l])
		joined[k++] = arr2[l++];
	joined[k] = NULL;
	(free(arr1), free(arr2));
	return (joined);
}


char	**get_last_split(char **splited)
{
	int		i;
	char	*expanded;
	char	**new_splt;
	char	**all_data;
	char	*mark;

	if (!splited)
		return (NULL);
	i = 0;
	all_data = NULL;
	while (splited[i])
	{
		expanded = ft_expand(splited[i++]);
		if (!expanded)
			continue ;
		wirldcard_expanding(&expanded);
		mark = ft_mark(expanded);
		new_splt = upgrade_split(expanded, mark);
		free(mark);
		if (expanded)
			free(expanded);
		all_data = join_double_array(all_data, new_splt);
	}
	return (all_data);
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

// int	inside_quote_expand(char *str)
// {
// 	if (!need_expand(str))
// 		return (0);
// 	return (1);
// }

// char	*get_first_arg(char *str)
// {
// 	char	**splt;
// 	char	*rtn_str;

// 	splt = ft_splt(str, SPACE);
// 	if (!splt)
// 		return (NULL);
// 	rtn_splt = ft_strdup(splt[0]);
// 	free_ptr(splt);
// 	return (rtn_str);
// }


// char	**get_splt_of_splt(char **splt)
// {
// 	char	**new_splt;
// 	int		i;
// 	char	*mark;

// 	i = 0;
// 	while (splt[i])
// 	{
// 		mark = ft_mark(splt[i]);
// 		new_splt = upgrade_split(splt[i], mark);
// 		fun(new_splt);
// 	}
// }

t_data	ft_data_new(char *cmd_line)
{
	t_data	data;
	char	**splt;
	char	*mark;

	wirldcard_expanding(&cmd_line);
	mark = ft_mark(cmd_line);
	splt = upgrade_split(cmd_line, mark);
	free(mark);
	splt = get_last_split(splt);
	if (!splt)
	{
		data.cmd = NULL;
		data.args = NULL;
		data.type = -1;
	}
	else
	{
		data.cmd = remove_quote(ft_expand(splt[0]));
		//wirldcard_expanding(&data.cmd);
		data.args = expand_args(splt);
		data.type = ft_type(splt[0]);
	}
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

	new_tree = upgrade_malloc(sizeof(t_tree), 0);
	//printf("BEFORE_REMOVE_PARA:%s\n", *line);
	new_tree->child_level = remove_first_parenthisis(line) + child_level;
	//printf("AFTER_REMOVE_PARA:%s\n", *line);
	new_tree->data = ft_data_new(*line);
	new_tree->parent = parent_add;
	new_tree->left_c = NULL;
	new_tree->right_c = NULL;
	new_tree->ambiguous = 0;
	return (new_tree);
}

void	parse_tree(char **line, t_tree *tree, char check)
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
		//printf("I MUST NOT BE HERE\n");
		tree->left_c = ft_tree_new(&splt_oper[0], tree, tree->child_level);
		tree->right_c = ft_tree_new(&splt_oper[2], tree, tree->child_level);
		tree->data = ft_data_new(splt_oper[1]);
		parse_tree(&splt_oper[0], tree->left_c, 1);
		parse_tree(&splt_oper[2], tree->right_c, 1);
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
			parse_tree(&splt_oper[0], tree->left_c, 1);
			parse_tree(&splt_oper[2], tree->right_c, 1);
		}
		else if (*line)
		{
			*line = reform_redirection(*line);
			tree->ambiguous = ambiguous_redirect(*line);
			//printf("BEFORE:%s\n", *line);
			if (check)
				*line = check_swap_red(*line);//free
			//printf("AFTER:%s\n", *line);
			mark = mark_redirection(*line, 0);
			mark_the_red_mark(mark);
			splt_oper = upgrade_split(*line, mark);
			// >> << > <
			if (need_split(mark) && len_ptr(splt_oper) > 2)
			{
				tree->left_c = ft_tree_new(&splt_oper[0], tree, tree->child_level);
				tree->right_c = ft_tree_new(&splt_oper[2], tree, tree->child_level);
				tree->data = ft_data_new(splt_oper[1]);
				parse_tree(&splt_oper[0], tree->left_c, 0);
				parse_tree(&splt_oper[2], tree->right_c, 0);
			}
			else if (len_ptr(splt_oper) == 2)
			{
				tree->data = ft_data_new(splt_oper[0]);
				tree->right_c = ft_tree_new(&splt_oper[1], tree, tree->child_level);
				//parse_tree(NULL, NULL, "left");
				parse_tree(&splt_oper[1], tree->right_c, 0);
			}
		}
	}
	return ;
}

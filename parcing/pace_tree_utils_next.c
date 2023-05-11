/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pace_tree_utils_next.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:38:43 by iantar            #+#    #+#             */
/*   Updated: 2023/05/11 15:39:09 by iantar           ###   ########.fr       */
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

int	ft_type(char *cmd)
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

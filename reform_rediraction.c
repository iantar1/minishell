/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reform_rediraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:45:25 by iantar            #+#    #+#             */
/*   Updated: 2023/03/29 23:39:24 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//you need to modify the cmd before spliting "ls > out -l" becames "ls -l > out"
// cat > outfile file1 file2... -> cat file1 file2 ... > outfile
// creat a functin take the args after the arg after > or < to the front of the cmd
// cmd < arg1 arg2 arg3 ...  -->  cmd  arg2 arg3 ... < arg1
// cmd > arg1 arg2 arg3 ...  -->  cmd  arg2 arg3 ... > arg1



static char	*mark_redirection(char *str)
{
	int		i;
	char	*mark;

	i = 0;
	mark = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			mark[i] = '2';
		else if (str[i] <= 32)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

static int	ft_pointerlen(char **ptrs)
{
	int	lenptr;

	lenptr = 0;
	while (ptrs[lenptr])
		lenptr++;
	return (lenptr);
}


char	**lst_to_str(t_list *lst)
{
	int		i;
	char	**str;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	str = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	while (lst)
	{
		str[i++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	str[i] = NULL;
	ft_lstclear(&tmp, free);
	return (str);
}

t_list	*str_to_lst(char **str)
{
	int		i;
	t_list	*tmp;
	t_list	*lst;

	i = 0;
	lst = ft_lstnew(str[i++]);
	tmp = lst;
	while (str[i])
	{
		lst->content = ft_lstnew(str[i]);
		i++;
	}
	free_ptr(str);
	return (tmp);
}

int	count_redirect(t_list *lst)
{
	
}

static int	index_of_redir(t_list *lst)
{
	int	index;

	index = 0;
	while (lst)
	{
		if (!ft_strncmp(lst->content, ">", 1)
			|| !ft_strncmp(lst->content, "<", 1))
			return (index);
		index++;
		lst = lst->next;
	}
	return (-1);
}

// static void	reform_it(t_list **lst)
// {
// 	int		i;
// 	int		len;
// 	int		index;
// 	t_list	*tmp;

// 	len = count_redirect(*lst);
// 	while (i < len)
// 	{
// 		index = index_of_redir(*lst);
// 		while (++i < index)
// 			tmp = tmp->next;
		
// 	}
// }


char	**reform_redirection(char *str)
{
	char	**splt_cmd;
	char	**rtn_cmd;
	char	*mark;
	t_list	*lst;

	mark = mark_redirection(str);
	splt_cmd = upgrade_split(str, mark);
	lst = str_to_lst(splt_cmd);
	//reform_it(&lst);
}

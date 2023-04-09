/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reform_rediraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:45:25 by iantar            #+#    #+#             */
/*   Updated: 2023/04/07 08:32:24 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//you need to modify the cmd before spliting "ls > out -l" becames "ls -l > out"
// cat > outfile file1 file2... -> cat file1 file2 ... > outfile
// creat a functin take the args after the arg after > or < to the front of the cmd
// cmd < arg1 arg2 arg3 ...  -->  cmd  arg2 arg3 ... < arg1
// cmd > arg1 arg2 arg3 ...  -->  cmd  arg2 arg3 ... > arg1


void	free_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		free(tmp->content);
		tmp = tmp->next;
	}
	free(lst);
}

char	*mark_redirection(char *str, int sp)
{
	int		i;
	char	*mark;

	i = 0;
	mark = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			mark[i] = '2';
		else if (str[i] <= 32 && sp)
			mark[i] = '1';
		else
			mark[i] = '0';
		i++;
	}
	mark[i] = '\0';
	return (mark);
}

char	**lst_to_arr(t_list *lst)
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

t_list	*arr_to_lst(char **str)
{
	int		i;
	t_list	*tmp;
	t_list	*lst;

	i = 0;
	lst = ft_lstnew(NULL);
	tmp = lst;
	while (str[i])
	{
		lst->next = ft_lstnew(str[i]);
		lst = lst->next;
		i++;
	}
	free_ptr(str);
	return (tmp);
}

int	count_redirect(t_list *lst)
{
	int	count;

	count = 0;
	lst = lst->next;
	while (lst)
	{
		if (!ft_strncmp(lst->content, ">", 1)
			|| !ft_strncmp(lst->content, "<", 1))
			count++;
			lst = lst->next;
	}
	return (count);
}

static int	index_of_redir(t_list *lst)
{
	int	index;

	index = 0;
	lst = lst->next;
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

//u need to check syntax error before using this function "<< >> < >"" must be flowed by a file_name"

static void	reform_it(t_list **lst)
{
	int		i;
	int		len;
	int		index;
	t_list	*tmp1;
	t_list	*tmp2;

	len = count_redirect(*lst);
	tmp1 = *lst;
	while (len)
	{
		index = index_of_redir(*lst);
		i = -1;
		tmp1 = *lst;
		while (++i < index)
			tmp1 = tmp1->next;
		tmp2 = tmp1->next;
		tmp1->next = tmp2->next->next;
		tmp2->next->next = NULL;
		ft_lstadd_back(lst, tmp2);
		len--;
	}
	tmp1 = *lst;
	*lst = (*lst)->next;
	free(tmp1);
}

char	*lst_to_str(t_list *lst)
{
	t_list	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = lst;
	str = lst->content;
	tmp = tmp->next;
	while (tmp)
	{
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, tmp->content);
		tmp = tmp->next;
	}
	return (str);
}

char	*reform_redirection(char *str)
{
	char	**splt_cmd;
	char	*rtn_str;
	char	*mark;
	t_list	*lst;

	mark = mark_redirection(str, SPACE);
	if (!need_split(mark))
		return (str);
	splt_cmd = upgrade_split(str, mark);
	lst = arr_to_lst(splt_cmd);
	reform_it(&lst);
	rtn_str = lst_to_str(lst);
	free_lst(lst);
	free(str);
	return (rtn_str);
}

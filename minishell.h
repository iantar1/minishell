/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:54:24 by iantar            #+#    #+#             */
/*   Updated: 2023/04/07 06:38:09 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPACE 32
# define AND 0
# define OR 1
# define PIPE 2
# define COMMAND 3
# define HERE_DOC 6
# define APPEND 7
# define _FILE 8
# define OUT 4
# define IN 5
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define WHITE   "\033[37m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFT/libft.h"

// typedef struct s_here_doc
// {
// 	struct s_here_doc	*next;
// 	void				*contet;
// }t_here_doc;

typedef struct s_file
{
	int		type;
	char	*filename;
}	t_files;

typedef struct s_data
{
	char	*cmd;
	int		type;//what is type?????
	char	**args;
}	t_data;

typedef struct s_heredoc
{
	char	*filename;
	int		fd;
}	t_heredoc;

typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*left_c;
	struct s_tree	*right_c;
	int				child_level;
	t_data			data;
	//t_heredoc		my_here_doc;
	//t_files			infile;
	//t_files			outfile;
	int				syntax_error;//when you have a syntax error asgin a 1 to it after that continue to open all here_doc then stop. 
}	t_tree;


typedef struct s_iofiles
{
	char	*filename;
	int		fd;
}	t_iofiles;

typedef struct s_env
{
	char			*line;
	char			*var_name;
	struct s_env	*head;
	struct s_env	*next;
}	t_env;

t_env	*g_env;

typedef struct s_vars
{
	char	*str;
	int		i;
	int		j;
	int		index;
	int		start;
	int		end;
}	t_vars;

void	parse_tree(char **line, t_tree *tree, char *str);
char	**upgrade_split(char *str, char *mark);
char	*ft_mark(char *str);
char	**get_env(char **env);
char	closed_quote(char *str);
char	*remove_quote(char *str);
t_env	*create_env(char **env);
//char	*expand(char *key, t_env *head_env);
int		need_expand(char *str);
char	*expand_mark(char *str);
char	*join_evrything(char **splt);
char	*ft_change_part(t_vars var, char *value, int *curser);
char	*ft_expand(char *str);
void	ft_expand_norm(t_vars var, char **splt);
char	*ft_change_part(t_vars var, char *value, int *curser);
char	*get_value(char *key, int len);
int		len_to_exp(char *str);
char	*join_evrything(char **splt);
char	*exp_from_env(char *key);
int		need_expand(char *str);
t_env	*new_line(char *line);
void	double_free(char **p);
char	closed_parenthesis(char *str);
int		is_here_needle(char *str, char *needle);
char	*ft_mark_operator(char *str);
char	*mark_the_mark_operator(char *mark);
char	*mark_first_parenthisis(char *str);
char	**reform_redirection(char *str);
char	*get_next_line(int fd);
char	*her_doc(char *lim, int to_save);
void	free_ptr(char **ptr);
char	**reform_redirection(char *str);
t_tree	*ft_tree_new(char **line, t_tree *parent_add, int child_level);
void	free_ptr(char **ptr);
char	*mark_redirection(char *str);
int		remove_first_parenthisis(char **str);
int		surrounded_parenthisis(char *mark);
int		need_split(char *mark);
void	remove_surrounded_sp(char **str);
char	**lst_to_str(t_list *lst);
t_list	*str_to_lst(char **str);
int		len_ptr(char **ptr);
char	*heredoc_expanding(char *str, char *lim);
void	check_here_doc(char **line);

#endif
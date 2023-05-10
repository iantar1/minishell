/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:54:24 by iantar            #+#    #+#             */
/*   Updated: 2023/05/10 20:25:57 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPACE 32
# define TAB 9
# define AND 0
# define OR 1
# define PIPE 2
# define HERE_DOC 6
# define APPEND 7
# define _FILE 8
# define OUT 4
# define IN 5

#define BRED "\e[1;31m"
#define REST "\e[0m"
#define BGRN "\e[1;32m"
#define BBLU "\e[1;34m"
#define YEL "\e[0;33m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/errno.h>
//# include "../parcing/LIBFT/libft.h"



// typedef struct s_here_doc
// {
// 	struct s_here_doc	*next;
// 	void				*contet;
// }t_here_doc;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

typedef struct s_file
{
	int		type;
	char	*filename;
}	t_files;


typedef struct s_heredoc
{
	char	*filename;
	int		fd;
}	t_heredoc;

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
//t_list	*_free_;

typedef struct s_vars
{
	char	*str;
	int		i;
	int		j;
	int		index;
	int		start;
	int		end;
	int		len;
	t_list	*tmp1;
	t_list	*tmp2;
}	t_vars;

typedef struct s_data
{
	char	*cmd;
	int		type;
	char	**args;
}	t_data;

typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*left_c;
	struct s_tree	*right_c;
	int				child_level;
	t_data			data;
	int				ambiguous;//exit status = 1
	int				valid_fd;
}	t_tree;



void	parse_tree(char **line, t_tree *tree, char check);
char	**upgrade_split(char *str, char *mark);
char	*ft_mark(char *str);
char	**get_env(char **env);
char	unclosed_quote(char *str);
char	*remove_quote(char *str);
t_env	*create_env(char **env);
int		need_expand(char *str);
char	*expand_mark(char *str);
char	*ft_change_part(t_vars var, char *value, int *curser);
char	*ft_expand(char *str);
void	ft_expand_norm(t_vars var, char **splt);
char	*ft_change_part(t_vars var, char *value, int *curser);
char	*get_value(char *key, int len);
int		len_to_exp(char *str);
char	*_join_evrything_(char **splt, int len_splt);
char	*join_evrything(char **splt);
char	*exp_from_env(char *key);
int		need_expand(char *str);
t_env	*new_line(char *line);
//void	double_free(char **p);
char	closed_parenthesis(char *str);
int		is_here_needle(char *str, char *needle);
char	*ft_mark_operator(char *str, int sp);
char	*mark_the_mark_operator(char *mark);
char	*mark_first_parenthisis(char *str);
char	*get_next_line(int fd);
char	her_doc(char *lim, int to_save, int fd);
void	free_ptr(char **ptr);
char	*reform_redirection(char *str);
t_tree	*ft_tree_new(char **line, t_tree *parent_add, int child_level);
void	free_ptr(char **ptr);
char	*mark_redirection(char *str, int sp);
int		remove_first_parenthisis(char **str);
int		surrounded_parenthisis(char *mark);
int		need_split(char *mark);
//void	remove_surrounded_sp(char **str);
t_list	*arr_to_lst(char **str);
char	**lst_to_arr(t_list *lst);
int		len_ptr(char **ptr);
char	*heredoc_expanding(char *str, char *lim);
int		check_here_doc(char **line);
void	free_lst(t_list *lst);
unsigned char	ft_strcmp(const char *s1, const char *s2);
int		ambiguous_redirect(char	*str);
t_list	*expand_wildcard(char *to_change, char *mask);
int		syntax_error(char *str);
void	ft_flag(char c, int *flag);
void	keep_last_redir(char **line);
void	wirldcard_expanding(char **line);
char	*lst_to_str(t_list *lst);
int		is_wildcard(char *mark);
char	*mark_wildcard(char *str);
int		inside_quotes(char *str);
char	*join_with_sp(char *str);
char	*check_swap_red(char *line);
void	inside_paranth(char c, char *inside, int flag);
void	*upgrade_malloc(size_t size, int to_free);
char	*strdup_upgrade(const char *s1);
char	*substr_upgrade(char const *s, unsigned int start, size_t len);
char	*strtrim_upgrade(char const *s1, char const *set);
char	*strjoin_upgrade(char const *s1, char const *s2);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isalnum(int c);
char	**ft_split(char const *s, char c);
void	ft_bzero(void *str, size_t n);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);

//execution
int		complet_filter(char *str, char *elem, char *mask, int check);
int		is_in_filter(char *str, char *elem, char *mask, int check);
void 	rl_replace_line(const char *text, int clear_undo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:54:24 by iantar            #+#    #+#             */
/*   Updated: 2023/03/23 12:47:17 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFT/libft.h"

typedef struct s_here_doc
{
	struct s_here_doc	*next;
	void				*contet;
}t_here_doc;

// typedef struct s_file
// {
// 	int        type;
// 	int        fd;
// 	char    *filename;
// }    t_files;

// typedef struct s_data
// {
// 	char    *cmd;
// 	int        type;
// 	char    **args;
// }    t_data;

// typedef struct s_tree
// {
// 	struct s_tree	*parent;
// 	struct s_tree	*left_c;
// 	struct s_tree	*right_c;
// 	int				child_lev41el;
// 	t_data			data;
// 	t_files			infile;
// 	t_files			outfile;
// }	t_tree;

typedef struct s_file
{
    int        type;
    int        open;
    int        close;
    int        file_id;
}    t_files;

typedef struct s_data
{
    char    *cmd;
    int        type;
    char    **args;
}    t_data;

typedef struct s_tree
{
    struct s_tree    *parent;
    struct s_tree    *left_c;
    struct s_tree    *right_c;
    int                child_level;
    t_data            data;
    t_files            infile;
    t_files            outfile;
}                    t_tree;

typedef struct s_iofiles
{
    char    *filename;
    int        id;
    int        fd;
}    t_iofiles;

t_iofiles    g_files[255];

typedef struct s_env
{
	char			*line;
	char			*var_name;
	int				exit_status;
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

char	**upgrade_split(char *str, char *mark);
char	*ft_mark(char *str);
char	**get_env(char **env);
char	closed_quote(char *str);
char	*remove_quote(char *str);
t_env	*create_env(char **env);
//char	*expand(char *key, t_env *head_env);
int		need_expand(char *str);
char	*expand_mark(char *str);
char	*ft_change_part(t_vars var, char *value, int *curser);
char	*ft_expand(char *str);
char	*ft_change_part(t_vars var, char *value, int *curser);
char	*get_value(char *key, int len);
int		len_to_exp(char *str);
char	*join_evrything(char **splt);
char	*exp_from_env(char *key, t_env *g_env);
int		need_expand(char *str);
t_env	*new_line(char *line);
void	double_free(char **p);
char	closed_parenthesis(char *str);
int		is_here_needle(char *str, char *needle);
char	*ft_mark_operator(char *str);
char	*mark_the_mark_operator(char *mark);
char	*mark_first_parenthisis(char *str);
char	**reform_redirection(char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:14:10 by iantar            #+#    #+#             */
/*   Updated: 2023/03/13 13:04:23 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFT/libft.h"

typedef struct s_command
{
}t_command;

typedef struct s_here_doc
{
	struct s_here_doc	*next;
	void				*contet;
}t_here_doc;

typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*right_child;
	struct s_tree	*left_child;
	void			*content;
}t_tree;

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

#endif
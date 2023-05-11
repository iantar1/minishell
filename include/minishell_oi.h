/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_oi.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:41:09 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/11 16:23:55 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_OI_H
# define MINISHELL_OI_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/errno.h>
# include <fcntl.h>
# include "../execution/ft_printf/ft_printf.h"
# include "minishell.h"
# define AND 0
# define OR 1
# define PIPE 2
# define COMMAND -1
# define HERE_DOC 6
# define APPEND 7
# define FILE 8
# define AMBIGUOUS_REDI 9
# define OUT 4
# define IN 5

// typedef struct s_env
// {
// 	char			*line;
// 	char			*var_name;
// 	struct s_env	*next;
// }	t_env;

// typedef struct s_file
// {
// 	int		type;
// 	int		open;
// 	int		close;
// 	int		file_id;
// }	t_files;

// typedef struct s_data
// {
// 	char	*cmd;
// 	int		type;//what is type?????
// 	char	**args;
// }	t_data;

// typedef struct s_tree
// {
// 	struct s_tree	*parent;
// 	struct s_tree	*left_c;
// 	struct s_tree	*right_c;
// 	int				child_level;
// 	t_data			data;
// 	int				ambiguous;//exit status = 1
// 	int				valid_fd;
// 	//int				syntax_error;
//when you have a syntax error asgin a 1 to
//it after that continue to open all here_doc then stop. 
// }	t_tree;

// typedef struct s_iofiles
// {
// 	char	*filename;
// 	int		id;
// 	int		fd;
// }	t_iofiles;
// typedef struct s_list
// {
// 	char			*data;
// 	struct s_list	*next;
// }	t_list;

// t_env	*g_env;
// int		exec_tree(t_tree *tree, int fds[2], int io[2], int level);
void	free_now(char **strs);
void	free_tree(t_tree *tree);
void	get_normale_attr(void);
void	modify_attr(void);
t_env	*create_env_oi(char **env);
char	**get_key_value_oi(char	*str);
int		exec(t_tree *tree, int in, int out);
int		exec_tree(t_tree *tree, int in, int out);
int		_execute(t_tree *tree, int in, int out);
int		print_exec_errors(char *full_path, char *cmd, int print);
char	*oi_itoa(int n);
void	sig_handler(int sig);
void	rl_replace_line(const char *text, int clear_undo);
int		handle_cmd(t_tree *tree, int out);
char	*get_variable(char *str);
int		show_env_in_order(void);
t_env	*new_line_oi(char	*line);
char	**oi_split(char const *s, char c);
size_t	oi_strlen(char *str);
char	*oi_strjoin(char *str, char *cmd);
int		oi_strcmp(const char *s1, const char *s2);
int		oi_strncmp(const char *s1, const char *s2, size_t n);
int		export_var(t_tree *tree);
int		is_in_env(char	*var);
char	*get_variable(char *str);
size_t	len_double_char(char **strs);
int		ft_free(char **str);
char	**get_key_value(char	*str);
char	symbole(char *str);
char	*oi_substr(char const *s, unsigned int start, size_t len);
char	*oi_mark(char *str);
char	*oi_strtrim(char const *s1, char const *set);
int		modify_var(char **var);
char	*classic_ft_strjoin(char const *s1, char const *s2);
int		handle_export(char *str);
char	*parse_value(char *val);
int		unset_var(t_tree *tree);
int		handle_unset(char *str);
int		ft_exit(t_data cmd);
char	*get_path(char *cmd, char *Path, int print);
int		update_env(char	*cmd, char *val);
int		cd(t_tree *tree, int out);
char	*get_env_line(char *var_name);
char	*pwd(void);
void	echo(t_tree	*tree, int out);
int		modify_env_var(char	*var_name, char *new_val);
size_t	list_size(void);
int		execute(char *str);
char	*oi_strchr(const char *s, int c);
int		sv_exit(int exit_status);
int		doubel_single_quotes(char	*str, char c);
int		oi_atoi(const char *str);
int		is_in_filter(char *str, char *elem, char *mask, int check);
void	handle(int sig);
char	**from_list_to_char(int check);
char	*free_oi(char **s1, char **s2);
char	*oi_strdup(char *s1);
int		sv_pid(int pid);
int		is_builtin(char *str);
int		subshell(t_tree *tree, int in, int out, int level);
int		wait_for(int *st, int pid2);
int		pipes(t_tree *tree, int in, int out);
int		redirect_io_file(t_tree *tree, int in, int out);
#endif
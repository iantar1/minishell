/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:04:28 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/10 17:59:08 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_oi.h"

t_env	*new_line_oi(char	*line)
{
	t_env			*node;
	char			**str;
	char			*trimed;
	int				i;

	i = 0;
	str = get_key_value_oi(line);
	if (!str)
		return (NULL);
	node = malloc(sizeof(t_env));
	trimed = oi_strtrim(str[0], "+");
	node->var_name = oi_strdup(trimed);
	if ((len_double_char(str) == 2)
		|| (str[1] && !str[1][0]))
		node->line = oi_strdup(str[1]);
	else if (len_double_char(str) == 1)
		node->line = NULL;
	node->next = NULL;
	if (str[0])
		free(str[0]);
	if (str[1])
		free(str[1]);
	if (str)
		free(str);
	return (free(trimed), node);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_dprintf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	rm_here_files(t_tree *tree)
{
	if (!tree)
		return ;
	rm_here_files(tree->left_c);
	if (tree->data.type == HERE_DOC)
		unlink(tree->right_c->data.cmd);
	rm_here_files(tree->right_c);
}

int	main_exec(char *str)
{
	t_tree	*tree;
	int		st;
	int		fd;

	fd = -1;
	st = 0;
	tree = NULL;
	if (check_here_doc(&str))
		return (0);
	signal(2, sig_handler);
	tree = ft_tree_new(&str, NULL, 0);
	parse_tree(&str, tree, 1);
	system("leaks minishell");
	st = subshell(tree, 0, 1, 0);
	system("leaks minishell");
	rm_here_files(tree);
	free_tree(tree);
	(signal(2, sig_handler), signal(3, SIG_IGN));
	return (1);
}

int	main(int ac, char *av[], char **env)
{
	char			*str;
	char			*trimed;
	struct termios	attr;

	((void)ac, signal(SIGQUIT, SIG_IGN), signal(SIGINT, &sig_handler));
	g_env = (get_normale_attr(), new_line_oi("?=0"));
	g_env->next = ((void)av, create_env_oi(env));
	while (1)
	{
		str = (tcgetattr(STDIN_FILENO, &attr), readline("minishell -$ "));
		if (!str)
			break ;
		trimed = (((str[0]) && add_history(str)), oi_strtrim(str, " \r\t	"));
		if (!trimed || !*trimed)
			;
		else if (syntax_error(trimed))
			(oi_putstr_fd("minishell: syntax error\n", 2), sv_exit(258));
		else
			main_exec(trimed);
		(tcsetattr(STDIN_FILENO, TCSANOW, &attr), (str && (free(str), 0)));
		str = NULL;
		(trimed && (free(trimed), 0));
		trimed = NULL;
	}
	return ((ft_dprintf(1, "exit\n")), oi_atoi(get_env_line("?")));
}

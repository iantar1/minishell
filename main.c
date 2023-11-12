/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <iantar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 10:04:28 by oidboufk          #+#    #+#             */
/*   Updated: 2023/11/12 21:18:03 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell_oi.h"
#include "include/minishell.h"


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
	free_now(str);
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
	st = subshell(tree, 0, 1, 0);
	rm_here_files(tree);
	(signal(2, sig_handler), signal(3, SIG_IGN));
	return (1);
}

int	main(int ac, char *av[], char **env)
{
	char			*str;
	char			*trimed;
	struct termios	attr;

	((void)ac, signal(SIGQUIT, SIG_IGN), signal(SIGINT, &sig_handler));
	g_env = new_line_oi("?=0");
	g_env->next = ((void)av, create_env_oi(env));
	while (1)
	{
		str = (tcgetattr(STDIN_FILENO, &attr), readline("minishell -$ "));
		if (!str)
			break ;
		trimed = (((str[0]) && (add_history(str), 1)), oi_strtrim(str, " \r\t	"));
		if (trimed && *trimed && syntax_error(trimed, 1))
			(upgrade_malloc(0, 1), ft_dprintf(2
					, "minishell: syntax error\n"), sv_exit(258));
		else if (trimed && *trimed)
			main_exec(trimed);
		(tcsetattr(STDIN_FILENO, TCSANOW, &attr), (str && (free(str), 0)));
		str = NULL;
		(trimed && (free(trimed), 0));
		trimed = NULL;
		upgrade_malloc(0, 1);
	}
	return ((ft_dprintf(1, "exit\n")), oi_atoi(get_env_line("?")));
}

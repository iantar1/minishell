/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:03:08 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/10 10:19:11 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

void	get_normale_attr(void)
{
	static struct termios	*attr;

	if (!attr)
		tcgetattr(STDIN_FILENO, attr);
	else
		tcsetattr(STDIN_FILENO, TCSAFLUSH, attr);
}

void	modify_attr(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:06:37 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/03 13:18:53 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../../include/minishell_oi.h"

int		ft_print_hex(unsigned int n, char c, int fd);
int		ft_print_ptr(void *n, int fd);
int		ft_dprintf(int fd, const char *str, ...);
void	ft_putchar_fd(char c, int fd);
int		oi_putstr_fd(char *s, int fd);
int		oi_putnbr_fd(int n, int fd);
size_t	ft_putnbr_fd_u(unsigned int n, int fd);
int		count_hex(size_t n);
#endif
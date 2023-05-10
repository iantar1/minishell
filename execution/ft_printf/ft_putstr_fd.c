/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:25:42 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/03 13:18:12 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	oi_putstr_fd(char *s, int fd)
{
	if (s)
	{
		write(fd, s, oi_strlen(s));
		return (oi_strlen(s));
	}
	else
	{
		write(1, "(null)", 6);
		return (6);
	}
}

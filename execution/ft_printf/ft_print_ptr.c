/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 10:25:06 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/03 13:18:12 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex_(size_t n)
{
	char		*str;

	str = "0123456789abcdef";
	if (n < 16)
		ft_putchar_fd(str[n], 1);
	else
	{
		ft_print_hex_(n / 16);
		ft_print_hex_(n % 16);
	}
	return (count_hex(n));
}

int	ft_print_ptr(void *n, int fd)
{
	oi_putstr_fd("0x", fd);
	ft_print_hex_((size_t)n);
	return (count_hex((size_t)n) + 2);
}

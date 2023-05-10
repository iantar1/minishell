/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:15:30 by oidboufk          #+#    #+#             */
/*   Updated: 2023/03/08 21:32:31 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_hex(size_t n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

int	ft_print_hex(unsigned int n, char c, int fd)
{
	char		*str;

	if (c == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	if (n < 16)
		ft_putchar_fd(str[n], fd);
	else
	{
		ft_print_hex(n / 16, c, fd);
		ft_print_hex(n % 16, c, fd);
	}
	return (count_hex(n));
}

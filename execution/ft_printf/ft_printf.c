/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:55:42 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/03 13:18:53 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check(char c, va_list ap, int fd)
{
	if (c == 'c')
	{
		ft_putchar_fd((char)va_arg(ap, int), fd);
		return (1);
	}
	else if (c == 's')
		return (oi_putstr_fd((char *)va_arg(ap, char *), fd));
	else if (c == 'd' || c == 'i')
		return (oi_putnbr_fd((int)va_arg(ap, int), fd));
	else if (c == 'u')
		return (ft_putnbr_fd_u((unsigned int)va_arg(ap, unsigned int), fd));
	else if (c == 'x')
		return (ft_print_hex(va_arg(ap, unsigned int), 'x', fd));
	else if (c == 'X')
		return (ft_print_hex(va_arg(ap, unsigned int), 'X', fd));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(ap, void *), fd));
	if (c != '%')
		ft_putchar_fd('%', fd);
	ft_putchar_fd(c, fd);
	return (2 - (c == '%'));
}

int	ft_dprintf(int fd, const char *str, ...)
{
	int		i;
	va_list	ap;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i], fd);
			count++;
		}
		else
			if (str[i + 1])
				count += ft_check(str[++i], ap, fd);
		i++;
	}
	va_end(ap);
	return (count);
}

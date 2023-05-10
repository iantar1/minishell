/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:40:43 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/03 13:18:53 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	number_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	number_len_u(size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	oi_putnbr_fd(int n, int fd)
{
	int	num;

	num = n;
	if (n == -2147483648)
	{
		oi_putstr_fd("-2147483648", fd);
	}
	else if (num < 0)
	{
		num *= -1;
		ft_putchar_fd('-', fd);
		oi_putnbr_fd(num, fd);
	}
	else if (num >= 0 && num <= 9)
	{
		num = num + '0';
		ft_putchar_fd(num, fd);
	}
	else
	{
		oi_putnbr_fd(num / 10, fd);
		ft_putchar_fd(num % 10 + '0', fd);
	}
	return (number_len(n));
}

size_t	ft_putnbr_fd_u(unsigned int n, int fd)
{
	size_t	num;

	num = n;
	if (num >= 0 && num <= 9)
	{
		num = num + '0';
		ft_putchar_fd(num, fd);
	}
	else
	{
		oi_putnbr_fd(num / 10, fd);
		ft_putchar_fd(num % 10 + '0', fd);
	}
	return (number_len_u(n));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oidboufk <oidboufk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:08:31 by oidboufk          #+#    #+#             */
/*   Updated: 2023/05/13 11:05:35 by oidboufk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_oi.h"

static int	number_len(size_t n)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static long	ft_abs(long n)
{
	if (n < 0)
		return (n * (-1));
	return (n);
}

char	*oi_itoa(int n)
{
	char	*str;
	int		i;
	int		len;
	long	num;

	num = ft_abs(n);
	len = number_len(num);
	if (n < 0)
		len++;
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[len - 1 - i++] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	str[len] = 0;
	return (str);
}

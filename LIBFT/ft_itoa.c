/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iantar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:34:25 by iantar            #+#    #+#             */
/*   Updated: 2022/10/23 09:05:05 by iantar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*revstr(char *str)
{
	int		j;
	char	sw;
	int		i;

	j = 0;
	i = 0;
	while (str[i])
		i++;
	i--;
	while (j < i)
	{
		sw = str[j];
		str[j] = str[i];
		str[i] = sw;
		i--;
		j++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	str[13];
	int		i;
	int		check;
	long	new;

	if (n == 0)
		return (ft_strdup("0"));
	check = 1;
	i = 0;
	new = n;
	if (new < 0)
	{
		check *= -1;
		new *= -1;
	}
	while (new > 0)
	{
		str[i++] = (new % 10) + '0';
		new /= 10;
	}
	str[i] = '\0';
	if (check > 0)
		return (ft_strdup(revstr(str)));
	return (ft_strjoin("-", revstr(str)));
}

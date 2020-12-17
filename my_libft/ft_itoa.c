/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <patutinaek@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/04/30 15:03:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			len1(int i)
{
	int				n;

	n = 1;
	if (i < 0)
		n++;
	while (i >= 10 || i <= -10)
	{
		n++;
		i = i / 10;
	}
	return (n);
}

char				*ft_itoa(int num)
{
	int				n;
	char			*res;
	int				count;
	long long int	i;

	i = (long long int)num;
	n = len1(i);
	res = (char *)malloc(n + 1);
	if (res == 0)
		return (0);
	if (i < 0)
	{
		res[0] = '-';
		i = i * (-1);
	}
	count = 1;
	while (i >= 10)
	{
		res[n - count] = i % 10 + '0';
		i = i / 10;
		count++;
	}
	res[n - count] = i + '0';
	res[n] = '\0';
	return (res);
}

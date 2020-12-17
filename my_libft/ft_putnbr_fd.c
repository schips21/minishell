/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <patutinaek@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/04/30 15:03:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr_fd(int n, int fd)
{
	long long int	num;

	if (fd >= 0)
	{
		num = (long long int)n;
		if (num < 0)
		{
			ft_putchar_fd('-', fd);
			num = num * (-1);
		}
		if (num >= 10)
		{
			ft_putnbr_fd(num / 10, fd);
		}
		num = num % 10;
		ft_putchar_fd(num + '0', fd);
	}
}

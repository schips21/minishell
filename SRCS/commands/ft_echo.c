/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:41:05 by dskittri          #+#    #+#             */
/*   Updated: 2020/11/26 17:41:07 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

void	ft_echo(t_info *info)
{
	int	i;
	int	fd;

	fd = 1;
	i = 1;
	while (i < info->args_num - 1)
	{
		ft_putendl_fd((info->args)[i], fd);
		i++;
	}
	if (i < info->args_num)
		ft_putstr_fd((info->args)[i], fd);
	if (info->args_num == 0 && info->n_flag == 0)
		ft_putchar_fd('\n', fd);
}

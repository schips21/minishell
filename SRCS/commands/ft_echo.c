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

	i = 1;
	while (i < info->args_num + 1)
	{
		ft_putstr_fd((info->args)[i], info->out);
		if (i == info->args_num && info->n_flag == 0)
			ft_putchar_fd('\n', info->out);
		else if (i != info->args_num)
			ft_putchar_fd(' ', info->out);
		i++;
	}
	if (info->args_num == 0 && info->n_flag == 0)
		ft_putchar_fd('\n', info->out);
}

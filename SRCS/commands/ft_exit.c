/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:41:32 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/29 19:41:34 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

int	ft_exit(t_info *info)
{
	int i;

	if (info->args_num == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(info->res_prev);
	}
	else
	{
		i = 0;
		while (info->args[1][i])
		{
			if (!(info->args[1][i] >= '0' && info->args[1][i] <= '9'))
				break;
			i++;
		}
		if (info->args[1][i] == '\0' && info->args_num == 1)
		{
			ft_putstr_fd("exit", 1);
			g_res = ft_atoi(info->args[1]);
			exit(ft_atoi(info->args[1]));
		}
		else if (info->args[1][i] == '\0' && info->args_num > 1)
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(info->args[0], 1);
			ft_putstr_fd(": too many arguments\n", 1);
			g_res = 1;
		}
		else
		{
			g_res = 255;
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(info->args[0], 1);
			ft_putstr_fd(": ", 1);
			ft_putstr_fd(info->args[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			exit(g_res);
		}
	}
	return (g_res);
}

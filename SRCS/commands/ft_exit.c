/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:41:32 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:12:28 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

int		ft_exit2(t_info *info, int i)
{
	if (info->args[1][i] == '\0' && info->args_num > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(info->args[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		g_res = 1;
	}
	else
	{
		g_res = 255;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(info->args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(info->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	return (g_res);
}

void	ft_exit(t_info *info)
{
	int i;

	if (info->args_num == 0)
	{
		ft_putstr_fd("exit\n", 2);
		exit(info->res_prev);
	}
	else
	{
		i = 0;
		while (info->args[1][i])
		{
			if (!(info->args[1][i] >= '0' && info->args[1][i] <= '9'))
				break ;
			i++;
		}
		if (info->args[1][i] == '\0' && info->args_num == 1)
		{
			ft_putstr_fd("exit", 2);
			g_res = ft_atoi(info->args[1]);
		}
		else
			g_res = ft_exit2(info, i);
		exit(g_res);
	}
}

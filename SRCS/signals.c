/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schips <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:50:37 by dskittri          #+#    #+#             */
/*   Updated: 2021/01/01 20:21:59 by schips           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

#include <stdio.h>

void		listener(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		write(1, "minishell: ", 11);
		if (g_ctrl_d == 1)
			g_ctrl_d = 2;
		g_res = 1;
	}
	else if (signal == SIGQUIT)
	{
		// g_ctrl_d = 1;
		write(1, "\b\b  \b\b", 6);
	}
}

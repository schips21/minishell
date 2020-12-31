/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:50:37 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:51:08 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

void		listener(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		write(1, "minishell: ", 11);
		g_res = 1;
	}
	else if (signal == SIGQUIT)
	{
		g_ctrl_d = 1;
		write(1, "\b\b  \b\b", 6);
	}
}

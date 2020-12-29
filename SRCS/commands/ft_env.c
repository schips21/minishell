/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:41:27 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/29 19:41:29 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

void	ft_env(t_env *env, int fd)
{
	while (env != NULL)
	{
		if (env->class == 1)
		{
			ft_putstr_fd(env->type, fd);
			ft_putstr_fd("=", fd);
			if (env->value != NULL)
				ft_putstr_fd(env->value, fd);
			ft_putchar_fd('\n', fd);
		}
		env = env->next;
	}
}

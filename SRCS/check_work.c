/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:41:00 by dskittri          #+#    #+#             */
/*   Updated: 2020/11/26 17:41:01 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

void	print_my_env(t_env *env)
{
	while (env != NULL)
	{
		printf("env:  %s=%s\n", env->type, env->value);
		env = env->next;
	}
}

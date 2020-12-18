/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:42:03 by dskittri          #+#    #+#             */
/*   Updated: 2020/11/26 18:32:40 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

int		ft_pwd(t_info *info, t_env *env, int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (errno != 0)
	{
		printf("error");
		ft_putendl_fd(strerror(errno), fd);
		return (-1);
	}
	ft_putendl_fd(pwd, fd);
	if (pwd)
		free(pwd);
	return (0);
}


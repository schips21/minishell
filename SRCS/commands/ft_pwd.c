/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:42:03 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:25:51 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

int		ft_pwd(t_info *info)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (errno != 0)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	ft_putendl_fd(pwd, 1);
	if (pwd)
		free(pwd);
	return (0);
}

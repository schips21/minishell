/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:32:11 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/04 14:16:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

char	*find_env(t_env *env, char *type)
{
	int	len;

	while (env != NULL)
	{
		len = ft_strlen(type);
		if(ft_strncmp(env->type, type, len) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int		ft_cd(t_info *info, t_env *env, int fd)
{
	int	res;

	if (info->args_num == 0)
		res = chdir(find_env(env, "HOME"));
	else
		chdir(info->args[1]);
	if (errno != 0)
	{
		ft_putstr_fd("cd: ", fd);
		if (res == -1)
			ft_putstr_fd("HOME not set", fd);
		else
			ft_putstr_fd(strerror(errno), 1);
		ft_putchar_fd('\n', fd);
		return (-1);
	}
	return (ch_pwd(env));
}
//в приницпе можно делать только с erno, но пусть так
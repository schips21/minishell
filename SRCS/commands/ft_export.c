/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:41:41 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:21:04 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

void		new_var_2(t_env *new, char *str)
{
	char	*i;

	free(new->value);
	if (ft_strchr(str, '=') != NULL)
	{
		i = ft_strchr(str, '=') + 1;
		new->value = ft_strdup(i);
		new->class = 1;
	}
	else
	{
		new->value = NULL;
		new->class = 2;
	}
}

void		new_var_3(char *str, char *type, t_env *env)
{
	char	*value;
	t_env	*new;
	char	*i;

	if (ft_strchr(str, '=') != NULL)
	{
		i = ft_strchr(str, '=') + 1;
		value = ft_strdup(i);
		if ((new = ft_envnew(type, value, 1)) == NULL)
			free_other(type, value);
	}
	else
	{
		value = NULL;
		if ((new = ft_envnew(type, value, 2)) == NULL)
			free_other(type, value);
	}
	ft_lstenv_back(&env, new);
}

int			new_var(t_env *env, char *str)
{
	char	*type;
	t_env	*new;

	if (ft_strchr(str, '=') != NULL)
		type = ft_strdup_sp(str, '=');
	else
		type = ft_strdup(str);
	if (type == NULL)
		return (errno);
	if ((new = find_env_env(env, type)) != NULL)
	{
		free(type);
		new_var_2(new, str);
	}
	else
		new_var_3(str, type, env);
	return (errno);
}

int			is_ok_sign(char a)
{
	if (a == '_')
		return (1);
	return (ft_isalpha(a));
}

int			ft_export(t_info *info, t_env *env, int fd)
{
	int		i;
	int		res;

	res = 0;
	if (info->args_num == 0)
		simple_export(env, fd);
	else
	{
		i = 1;
		while (info->args[i] != NULL)
		{
			if (is_ok_sign(info->args[i][0]) == 0)
				res = export_error(info->args[i], 2, 1);
			else
				errno = new_var(env, info->args[i]);
			i++;
		}
		if (errno != 0)
			return (export_error(info->args[i], 2, 2));
	}
	return (res);
}

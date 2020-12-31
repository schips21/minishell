/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:41:37 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:18:13 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

void		ft_chng_elem(t_env **prev, t_env **fir, t_env **sec, t_env **start)
{
	t_env	*tmp;

	(*fir)->next = (*sec)->next;
	(*sec)->next = *fir;
	tmp = *sec;
	*sec = *fir;
	*fir = tmp;
	if (*prev == NULL)
		*start = *fir;
	else
		(*prev)->next = *fir;
}

t_env		*sort_env(t_env *start)
{
	t_env	*final;
	t_env	*first;
	t_env	*second;
	t_env	*previous;

	final = NULL;
	while (final != start)
	{
		previous = NULL;
		second = start->next;
		first = start;
		while (second != final)
		{
			if (ft_strncmp(first->type, second->type, 150) > 0)
				ft_chng_elem(&previous, &first, &second, &start);
			previous = first;
			first = second;
			second = second->next;
		}
		final = first;
	}
	return (start);
}

t_env		*copy_env(t_env *env)
{
	t_env	*copy_start;
	t_env	*copy;
	char	*new_type;
	char	*new_value;

	new_type = ft_strdup(env->type);
	new_value = ft_def_strdup(env->value);
	copy_start = ft_envnew(new_type, new_value, env->class);
	env = env->next;
	while (env != NULL)
	{
		new_type = ft_strdup(env->type);
		new_value = ft_def_strdup(env->value);
		copy = ft_envnew(new_type, new_value, env->class);
		ft_lstenv_back(&copy_start, copy);
		env = env->next;
	}
	return (copy_start);
}

void		print_export(t_env *env, int fd)
{
	while (env != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env->type, fd);
		if (env->value != NULL)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
}

void		simple_export(t_env *env, int fd)
{
	t_env	*new;

	new = sort_env(copy_env(env));
	print_export(new, fd);
	free_env(new);
}

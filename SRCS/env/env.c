/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:41:33 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:31:59 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

void		*free_env(t_env *env)
{
	t_env	*next_env;

	while (env != NULL)
	{
		next_env = env->next;
		if (env->type != NULL)
			free(env->type);
		if (env->value != NULL)
			free(env->value);
		free(env);
		env = next_env;
	}
	return (NULL);
}

t_env		*ft_envlast(t_env *env)
{
	t_env	*last;

	if (env == 0)
		return (0);
	last = env;
	while (last->next)
		last = (last->next);
	return (last);
}

void		*free_other(char *type, char *value)
{
	if (type != NULL)
		free(type);
	if (value != NULL)
		free(value);
	return (NULL);
}

t_env		*ft_envnew(void *type, void *value, int class)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new)
	{
		(new->next) = NULL;
		(new->type) = type;
		(new->value) = value;
		(new->class) = class;
	}
	return (new);
}

void		ft_lstenv_back(t_env **env, t_env *new)
{
	t_env	*element;

	if (*env && new)
	{
		element = ft_envlast(*env);
		element->next = new;
	}
	else if (new)
	{
		*env = new;
	}
}

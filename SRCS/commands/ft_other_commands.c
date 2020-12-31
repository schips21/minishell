/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:41:57 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:25:11 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

int					env_len_class_1(t_env *env)
{
	int				i;

	i = 0;
	while (env != NULL)
	{
		if (env->class == 1)
			i++;
		env = env->next;
	}
	return (i);
}

char				**from_env_to_array(t_env *env)
{
	char			**envp;
	int				i;

	i = 0;
	if ((envp = malloc((sizeof(char **)) * (env_len_class_1(env) + 1))) == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (env->class == 1)
		{
			if (env->value == NULL)
				envp[i] = ft_strjoin_path(env->type, "", '=');
			else
				envp[i] = ft_strjoin_path(env->type, env->value, '=');
			if (envp[i] == NULL)
			{
				free_arr(envp);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int					error_errno(t_info *info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(info->args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (errno);
}

int					other_error(t_info *info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(info->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
	return (errno);
}

int					if_file_here(t_info *info, DIR *new)
{
	struct dirent	*files;
	int				len;

	while ((files = readdir(new)) != NULL && errno == 0)
	{
		len = ft_strlen(info->args[0]);
		if (len == files->d_namlen &&
			(ft_strncmp(files->d_name, info->args[0], len)) == 0)
		{
			closedir(new);
			return (1);
		}
	}
	closedir(new);
	return (0);
}

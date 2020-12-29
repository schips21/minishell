/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schips <schips@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:22:59 by schips            #+#    #+#             */
/*   Updated: 2020/12/29 21:48:04 by schips           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

char	*pars_dollar_create_env(char *line, int *i, int count)
{
	int		j;
	char	*env_var;

	if (!(env_var = malloc(sizeof(char) * (count + 1))))
		return (0);
	j = 0;
	while (j < count)
		env_var[j++] = line[(*i)++];
	env_var[j] = '\0';
	return (env_var);
}

char	*pars_dollar(char *line, int *i)
{
	int		count;
	int		j;

	count = 0;
	(*i)++;
	j = *i;
	while (((line[j] >= 48 && line[j] <= 57) || (line[j] >= 65 && line[j] <= 90)
	|| (line[j] >= 97 && line[j] <= 122) || line[j] == '_') && line[j] != '\0')
	{
		count++;
		j++;
	}
	return (pars_dollar_create_env(line, i, count));
}

void	pars_dollar_env(t_info *parsed, t_env *env, int arg_i, char *env_str)
{
	char	*path_env;
	char	*finded_end;
	int		i;

	path_env = NULL;
	if (env_str[0] == '\0')
		finded_end = ft_strdup("$");
	else
		finded_end = find_env(env, env_str);
	if (finded_end)
		path_env = ft_strdup(finded_end);
	free(env_str);
	i = 0;
	if (path_env)
	{
		while (path_env[i] != '\0')
			new_letter(parsed, arg_i, path_env[i++]);
		free(path_env);
	}
}

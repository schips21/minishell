/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:36:58 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/04 15:18:21 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

/*
res используется для обработки ошибок, сообщение об ошибке будет внутри функции,
при ошибке res == -1
необходимо для удобного выхода из процесса
*/

/*где pipe, redirects обрабатывать?
int/out fd будут поступать вместе с info*/

char	*ft_def_strdup(char *s1)
{
	size_t	len;
	char	*p;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen((char*)s1);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i != len + 1)
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}

int		command_execution(t_info *info, t_env *env)
{
	int res;
	res = 0;
	errno = 0;
	if (ft_strncmp(info->args[0], "cd", 3) == 0)
		res = ft_cd(info, env);
	else if (ft_strncmp(info->args[0], "pwd", 4) == 0)
		res = ft_pwd(info);
	else if (ft_strncmp(info->args[0], "export", 7) == 0)
		res = ft_export(info, env, info->out);
	else if (ft_strncmp(info->args[0], "unset", 6) == 0)
		res = ft_unset(info, env);
	else if (ft_strncmp(info->args[0], "env", 4) == 0)
		ft_env(env, info->out);
	else if (ft_strncmp(info->args[0], "echo", 5) == 0)
		ft_echo(info);
	else if (ft_strncmp(info->args[0], "exit", 5) == 0)
		ft_exit(info);
	else
		res = ft_other_commands(info, env);
	return (res);
}


/*
пока не трогаю пайпы
пайпы выполняют команды параллельно
*/

int		process(t_env *env, t_info *info)
{
	int	res;

	res = redirect_processing(info);
	if (res != 0)
		return (res);
	res = command_execution(info, env);
//	printf("echo $?\n%i\n", res);
	if (info->in != 0)
		close(info->in);
	if (info->out != 1)
		close(info->out);
	return (res);
}
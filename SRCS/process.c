/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:36:58 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/27 14:14:46 by dskittri         ###   ########.fr       */
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

int		command_execution(t_info *info, t_env *env, t_general *general)
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
		res = ft_other_commands(info, env, general);
	return (res);
}


/*
пока не трогаю пайпы
пайпы выполняют команды параллельно
*/

void	info_fullfillment(t_info *info)
{
	info->out = 1;
}

int		process(t_env *env, t_info *info, t_general *general)
{
	int	res;

	res = 0;
	general->other_command = 0;
	if (info->pipe == 1)
	{
		general->other_command = 1;
		general->pipe_in_prev_command = 1;
		if (pipe(general->pipe_fd) < 0)
			return (-1);
		//dup2(general->pipe_fd[0], 0);//замена stdin дескриптора на дескриптор pipe[0]
		//dup2(general->pipe_fd[1], 1);//замена stdout дескриптора на дескриптор pipe[1]
		res = command_execution(info, env, general);
		//заменяем все файловые дескрипторы и на вход и на выход
	}
	else
	{
		if (general->pipe_in_prev_command == 1)
		{
			general->other_command = 2;
			general->pipe_in_prev_command = 0;
			//char buffer[200];
			//dup2(general->pipe_fd[0], 0);
			//read(0, buffer, 100);
			//printf("%s\n", buffer);
			/*close(general->pipe_fd[1]);
			dup2(general->dup_out, 1);
			char buffer[200];
			read(0, buffer, 100);
			printf("%s\n", buffer);*/
			//замена дескрипторов на вывод, выполнение команды, замена дескрипторов на ввод
			res = command_execution(info, env, general);
			printf("HELLO\n");
			ft_putendl_fd("Hello", 2);
			//close(general->pipe_fd[0]);
			//dup2(general->dup_in, 0);
		}
		else
			res = command_execution(info, env, general);
		//выполнение команды без пайпов
	}
	ft_putendl_fd("Hello", 2);
	// if необходима обратная замена файловых дескрипторов (команда до имела пайп, данна нет)
	// меняем братно файловые дескрипторы
	return (res);
}



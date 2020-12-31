/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:36:58 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:07:39 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

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

int		if_other_command(t_info *info)
{
	int res;

	res = 0;
	if (ft_strncmp(info->args[0], "cd", 3) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "pwd", 4) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "export", 7) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "unset", 6) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "env", 4) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "echo", 5) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "exit", 5) == 0)
		res = 1;
	return (res);
}

int		excex_command_new(char *command, t_info *info, t_env *env)
{
	char		**envp;
	int			res;

	envp = from_env_to_array(env);
	execve(command, info->args, envp);
	other_error(info);
	return (0);
}

int		ft_other_commands_2_new(t_info *info, t_env *env, char **path_arr, t_general *general)
{
	int				i;
	DIR				*new;
	char			*full_path;

	i = 0;
	full_path = NULL;
	while ((path_arr[i]) && errno == 0)
	{
		new = opendir(path_arr[i]);
		if (errno != 0)
			errno = 0;
		else if ((if_file_here(info, new)) == 1)
		{
			if (!(full_path = ft_strjoin_path(path_arr[i], info->args[0], '/')))
				return (errno);
			i = excex_command_new(full_path, info, env);
			free(full_path);
			return (i);
		}
		i++;
	}
	if (errno != 0)
		return (error_errno(info));
	full_path = info->args[0];
	if (ft_strchr(info->args[0], '/') == 0)
		return (other_error(info));
	full_path = info->args[0];
	return (excex_command_new(full_path, info, env));
}

int		ft_other_commands_new(t_info *info, t_env *env, t_general *general)
{
	char	*path;
	char	**path_arr;
	int		res;

	path = find_env(env, "PATH");
	if (path == NULL)
		return (excex_command_new(info->args[0], info, env));
	path_arr = ft_split(path, ':');
	if (path_arr == NULL)
		return (error_errno(info));
	res = ft_other_commands_2_new(info, env, path_arr, general);
	free_arr(path_arr);
	//if (errno != 0)
	//return (other_error(info));
	return (res);
}

int		parents_cmnd_exec(t_info *info, t_env *env)
{
	int res;

	res = 0;
	if (ft_strncmp(info->args[0], "cd", 3) == 0)
		res = ft_cd(info, env);
	else if (ft_strncmp(info->args[0], "export", 7) == 0)
		res = ft_export(info, env, info->out);
	else if (ft_strncmp(info->args[0], "unset", 6) == 0)
		res = ft_unset(info, env);
	else if (ft_strncmp(info->args[0], "exit", 5) == 0)
		ft_exit(info);
	return (res);
}

int		if_parent_process(t_info *info, t_env *env)
{
	int res;

	res = 0;
	if (ft_strncmp(info->args[0], "cd", 3) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "export", 7) == 0 && info->args[1] != NULL)
		res = 1;
	else if (ft_strncmp(info->args[0], "unset", 6) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "exit", 5) == 0)
		res = 1;
	return (res);
}

void		listener2(int signal)
{
	if (signal == SIGINT)//ctrl-c
	{
		//write(1, "\n", 2);
	}
}

int		command_execution(t_info *info, t_env *env, t_general *general)
{
	int			res;
	pid_t		pid;
	int			stat;

	res = 0;
	errno = 0;
	res	= redirect_processing(info);
	if (res != 0)
		return (res);
	if (if_parent_process(info, env))
	{
		res = parents_cmnd_exec(info, env);
		return (res);
	}
	if (general->other_command == 2 && info->left_redir == 0) //последняя команда после нечетного количества пайпов
	{
		close(general->pipe_fd[1]);
		dup2(general->pipe_fd[0], 0);
		close(general->pipe_fd[0]);
		dup2(general->dup_out, 1);
	}
	else if (general->other_command == 3 && info->left_redir == 0) //промежуточная команда после нечетного пайпа
	{
		close(general->pipe_fd[1]);
		dup2(general->pipe_fd[0], 0);
		close(general->pipe_fd[0]);
		general->pipe_fd[0] = -2;
		general->pipe_fd[1] = -2;
	}
	else if (general->other_command == 6 && info->left_redir == 0) //промежуточная команда после четного пайпа
	{
		close(general->pipe_fd2[1]);
		dup2(general->pipe_fd2[0], 0);
		close(general->pipe_fd2[0]);
		general->pipe_fd2[0] = -2;
		general->pipe_fd2[1] = -2;
	}
	else if (general->other_command == 4 && info->left_redir == 0) //последняя команда после четного количества пайпов
	{
		close(general->pipe_fd2[1]);
		dup2(general->pipe_fd2[0], 0);
		close(general->pipe_fd2[0]);
	}
	pid = fork();
	if (pid < 0)
		return (error_errno(info));
	else if (pid == 0)
	{
		if ((general->other_command == 1 || general->other_command == 6) && info->right_redir == 0)//первая команда перед пайпом
		{
			close(general->pipe_fd[0]);
			dup2(general->pipe_fd[1], 1);
			close(general->pipe_fd[1]);
		}
		else if (general->other_command == 3 && info->right_redir == 0) //промежуточная команда
		{
			close(general->pipe_fd2[0]);
			dup2(general->pipe_fd2[1], 1);
			close(general->pipe_fd2[1]);
		}
		errno = 0;
		res = 0;
		if (if_other_command(info) == 0)
			res = ft_other_commands_new(info, env, general);
		else
		{
			if (ft_strncmp(info->args[0], "pwd", 4) == 0)
				res = ft_pwd(info);
			else if (ft_strncmp(info->args[0], "export", 7) == 0)
				res = ft_export(info, env, info->out);
			else if (ft_strncmp(info->args[0], "env", 4) == 0)
				ft_env(env, info->out);
			else if (ft_strncmp(info->args[0], "echo", 5) == 0)
				ft_echo(info);
		}
		exit(res);
	}
	signal(SIGINT, SIG_IGN);//
	signal(SIGINT, listener2);//
	waitpid(pid, &stat, WUNTRACED);//ошибка не чувствительня к сигналам
	if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == 2)
			stat = 130;
		else if (WTERMSIG(stat) == 3)
			stat = 131;
	}
	else
		stat = WEXITSTATUS(stat);
	signal(SIGINT, listener);
	signal(SIGQUIT, listener);
	return (stat);
}

void	info_fullfillment(t_info *info)
{
	info->out = 1;
}

int		process(t_env *env, t_info *info, t_general *general)
{
	int	res;

	res = 0;
	if (info->args == NULL)
	{
		redirect_processing(info);
		return (g_res);
	}
	general->other_command = 0;
	if (info->pipe == 1 && general->prev_pipe != 1)
	{
		general->prev_pipe = 1;
		if (pipe(general->pipe_fd) < 0)
			return (-1);
		general->other_command = 1;
		res = command_execution(info, env, general);
	}
	else
	{
		if (general->prev_pipe == 1 && info->pipe == 0) //команда для последнего пайпа, если их было четное количество
		{
			if (general->pipe_fd2[0] == -2 && general->pipe_fd2[1] == -2)
				general->other_command = 2;
			else
				general->other_command = 4;
			general->prev_pipe = 0;
			res = command_execution(info, env, general);
		}
		else if (general->prev_pipe == 1 && info->pipe == 1) //промежуточная команда
		{
			if (general->pipe_fd2[0] == -2 && general->pipe_fd2[1] == -2)
			{
				general->other_command = 3;
				if (pipe(general->pipe_fd2) < 0)
					return (-1);
			}
			else
			{
				general->other_command = 6;
				if (pipe(general->pipe_fd) < 0)
					return (-1);
			}
			general->prev_pipe = 1;
			res = command_execution(info, env, general);
		}
		else
			res = command_execution(info, env, general);
	}
	return (res);
}

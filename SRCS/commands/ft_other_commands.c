#include "../shell_header.h"

//int READ_END = 0;
//int WRITE_END = 1;

void		free_arr(char **array)
{
	int		i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

/*в каком виде принимает полностью*/ 

int			env_len_class_1(t_env *env)
{
	int i;

	i = 0;
	while (env != NULL)
	{
		if (env->class == 1)
			i++;
		env = env->next;
	}
	return (i);
}

char		**from_env_to_array(t_env *env)
{
	char	**envp;
	int		i;

	i = 0;
	envp = malloc((sizeof(char **)) * (env_len_class_1(env) + 1));
	if (envp == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (env->class == 1)
		{
			if (env->value == NULL)
				envp[i] = ft_strjoin_path(env->type, "");
			else
				envp[i] = ft_strjoin_path(env->type, env->type);
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

int			error_errno(t_info *info)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(info->args[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(strerror(errno), 1);
	return (errno);
}

int		other_error(t_info *info)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(info->args[0], 1);
	ft_putendl_fd(": command not found", 1);
	//ft_putendl_fd(strerror(errno), 1);
	return (errno);
}

int			excex_command(char *command, t_env *env, t_info *info, t_general *general)
{
	pid_t	pid;
	//int		status;
	char	**envp;
	//int		statusCode;


	//statusCode = 0;
	envp = from_env_to_array(env);
	pid = fork();
	if (pid < 0)
		return (error_errno(info));
	if (general->other_command == 2)
	{
		close(general->pipe_fd[1]);
		dup2(general->pipe_fd[0], 0);
		close(general->pipe_fd[0]);
	}
	else if (pid == 0)
	{
		//dup2(info->dup_out, 1);
		if (general->other_command == 1)
		{
			close(general->pipe_fd[0]);
			dup2(general->pipe_fd[1], 1);
			close(general->pipe_fd[1]);
		}
		/*else if (general->other_command == 2)
		{
			close(general->pipe_fd[1]);
			dup2(general->pipe_fd[0], 0);
			close(general->pipe_fd[0]);
		}*/
		execve(command, info->args, envp);//после execve ничего не работает, как тогда вернуть значениие
		ft_putendl_fd("After execve", 2);
		exit(0);
	}
	else
	{
		ft_putendl_fd("Before wait pid", 2);
		wait(NULL);
		//waitpid(pid, &status, 0);
		ft_putendl_fd("After wait pid", 2);
		/*if (WIFEXITED(status))
		{
			statusCode = WEXITSTATUS(status);
		}*/
	}
	ft_putendl_fd("Hello", 2);
	return (0);
}

int					if_file_here(t_info *info, DIR *new)
{
	struct dirent	*files;
	int				len;

	while ((files = readdir(new))!= NULL && errno == 0)
	{
		len = ft_strlen(info->args[0]); 
		if (len == files->d_namlen && (ft_strncmp(files->d_name, info->args[0], len)) == 0)
		{
			closedir(new);
			return (1);
		}
	}
	closedir(new);
	return (0);
}

//если команды нет в папках path, надо проверить, есть ли команда в нашей актуальной папке, если есть, то выполнять, если нет, то выход: команда не найдена

int			ft_other_commands_2(t_info *info, t_env *env, char **path_arr, t_general *general)
{
	int				i;
	DIR				*new;
	char			*full_path;

	i = 0;
	while ((path_arr[i]) && errno == 0)
	{
		new = opendir(path_arr[i]);
		if (errno != 0)
			errno = 0;
		else if ((if_file_here(info, new)) == 1)
		{
			if ((full_path = ft_strjoin_path(path_arr[i], info->args[0])) == NULL)	//malloc
				return (errno);
			i = excex_command(full_path, env, info, general);
			free(full_path);
			return (i);
		}
		i++;
	}
	if (errno != 0)
		return (error_errno(info));
	return (excex_command(info->args[0], env, info, general));
}

int			ft_other_commands(t_info *info, t_env *env, t_general *general)
{
	char	*path;
	char	**path_arr;
	int		res;

	path = find_env(env, "PATH");
	if (path == NULL)
		return (excex_command(info->args[0], env, info, general));
	path_arr = ft_split(path, ':');
	if (path_arr == NULL)
		return (error_errno(info));
		//return (error_errno(errno, 1));
	res = ft_other_commands_2(info, env, path_arr, general);
	free_arr(path_arr);
	//if (errno != 0)
		//return (other_error(info));
		//return (error_errno(errno, 1));
	return (res);
}
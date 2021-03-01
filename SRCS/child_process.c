#include "shell_header.h"

int			excex_command_new(char *command, t_info *info, t_env *env)
{
	char	**envp;
	int		res;

	envp = from_env_to_array(env);
	res = execve(command, info->args, envp);
	other_error(info);
	return (errno);
}

int			ft_other_commands_2_new(t_info *info, t_env *env, char **path_arr)
{
	int		i;
	DIR		*new;
	char	*full_path;

	i = 0;
	if (ft_strchr(info->args[0], '/') != 0)
		return (excex_command_new(info->args[0], info, env));
	while ((path_arr[i]) && errno == 0)
	{
		new = opendir(path_arr[i]);
		errno = 0;
		if ((if_file_here(info, new)) == 1)
		{
			if (!(full_path = ft_strjoin_path(path_arr[i], info->args[0], '/')))
				return (errno);
			excex_command_new(full_path, info, env);
		}
		i++;
	}
	if (errno != 0)
		return (error_errno(info));
	return (other_error(info));
}

int			ft_other_commands_new(t_info *info, t_env *env)
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
	res = ft_other_commands_2_new(info, env, path_arr);
	free_arr(path_arr);
	return (res);
}

int			our_child_commands(t_env *env, t_info *info, t_general *general)
{
	int		res;

	res = 0;
	if (ft_strncmp(info->args[0], "pwd", 4) == 0)
		res = ft_pwd();
	else if (ft_strncmp(info->args[0], "export", 7) == 0)
		res = ft_export(info, env, info->out);
	else if (ft_strncmp(info->args[0], "env", 4) == 0)
		ft_env(env, info->out);
	else if (ft_strncmp(info->args[0], "echo", 5) == 0)
		ft_echo(info);
	else if (ft_strncmp(info->args[0], "exit", 5) == 0)
		ft_exit(info, general);
	return (res);
}

int			execution_child(t_info *info, t_env *env, t_general *general)
{
	int		res;

	pipe_execution_child(general, info);
	if (if_other_command(info) == 0)
		res = ft_other_commands_new(info, env);
	else
		res = our_child_commands(env, info, general);
	exit(res);
}

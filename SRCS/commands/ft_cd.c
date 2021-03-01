#include "../shell_header.h"

char	*find_env(t_env *env, char *type)
{
	int	len;

	while (env != NULL)
	{
		len = ft_bigger_str(env->type, type);
		if (ft_strncmp(env->type, type, len) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int		cd_error(void)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (errno);
}

int		ch_pwd(t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->type, "PWD", 4) == 0)
		{
			free(env->value);
			env->value = getcwd(NULL, 0);
			if (errno != 0)
				cd_error();
			return (errno);
		}
		env = env->next;
	}
	return (0);
}

int		ft_cd2(int res, t_info *info)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (res == -1)
		ft_putendl_fd("HOME not set", 2);
	else
	{
		ft_putstr_fd(info->args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (1);
}

int		ft_cd(t_info *info, t_env *env)
{
	int		res;
	char	*old_pwd;
	t_env	*env_old_pwd;

	if ((env_old_pwd = find_env_env(env, "OLDPWD")) != NULL)
	{
		old_pwd = getcwd(NULL, 0);
		if (old_pwd == NULL)
			return (cd_error());
		env_old_pwd->class = 1;
		if (env_old_pwd->value != NULL)
		{
			free(env_old_pwd->value);
			env_old_pwd->value = NULL;
		}
		env_old_pwd->value = old_pwd;
	}
	if (info->args_num == 0)
		res = chdir(find_env(env, "HOME"));
	else
		chdir(info->args[1]);
	if (errno != 0)
		return (ft_cd2(res, info));
	return (ch_pwd(env));
}

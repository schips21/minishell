#include "../shell_header.h"

void	export_error(char *err, int fd)
{
	ft_putstr_fd("export: `", fd);
	ft_putstr_fd(err, fd);
	ft_putstr_fd("': not a valid identifier\n", fd);
}

void	new_var(t_env *env, char *str)
{
	char 	*type;
	char 	*value;
	char	*i;
	t_env	*new;
	
	if (ft_strchr(str, '=') != NULL)
	{
		type = ft_strdup_sp(str, '=');
		i = ft_strchr(str, '=') + 1;
		value = ft_strdup(i);
		new = ft_envnew(type, value, 1);	
	}
	else
	{
		type = ft_strdup(str);
		value = NULL;
		new = ft_envnew(type, value, 2);
	}
	ft_lstenv_back(&env, new);
}

int		ft_export(t_info *info, t_env *env, int fd)
{
	int	i;

	if (info->args_num == 0)
		simple_export(env, fd);
	else
	{
		i = 1;
		while (info->args[i] != NULL)
		{
			if (ft_isalpha(info->args[i][0]) == 0)
				export_error(info->args[i], 1);
			else
				new_var(env, info->args[i]);
			i++;
		}
		if (errno != 0)
		{
			ft_putendl_fd(strerror(errno), 1);
			return(-1);
		}
	}
	return (0);
}
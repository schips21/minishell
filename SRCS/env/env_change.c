#include "../shell_header.h"

int		ch_old_pwd(t_env *env)
{
	t_env	*new;
	char	*type;
	char	*value;

	type = ft_strdup("OLDPWD");
	value = getcwd(NULL, 0);
	new = ft_envnew(type, value, 1);
	if (errno != 0)
	{
		strerror(errno);
		return (-1);
	}
	ft_lstenv_back(&env, new);
	return (0);
}


int		ch_pwd(t_env *env)
{
	while (env != NULL)
	{
		if(ft_strncmp(env->type, "PWD", 4) == 0)
		{
			free(env->value);
			env->value = getcwd(NULL, 0);
			if (errno != 0)
			{
				strerror(errno);
				return (-1);
			}
			else
				break ;
		}
		env = env->next;
	}
	return (ch_old_pwd(env));
}
#include "../shell_header.h"

t_env		*get_env_type_value(char **envp, int count)
{
	char	*i;
	t_env	*env;
	char	*type;
	char	*value;

	type = ft_strdup_sp(envp[count], '=');
	i = ft_strchr(envp[count], '=') + 1;
	value = ft_strdup(i);
	env = ft_envnew(type, value, 1);
	return (env);
}

t_env		*get_env2(t_env *first)
{
	char	*old_pwd;
	t_env	*env;

	if ((find_env_env(first, "OLDPWD")) == NULL)
	{
		old_pwd = ft_strdup("OLDPWD");
		if (old_pwd == NULL)
			return (free_env(first));
		env = ft_envnew(old_pwd, NULL, 2);
		if (env == NULL)
		{
			free(old_pwd);
			return (free_env(first));
		}
		ft_lstenv_back(&first, env);
	}
	return (first);
}

t_env		*get_env(char **envp, t_env *first)
{
	t_env	*env;
	int		count;

	count = 0;
	first = NULL;
	first = get_env_type_value(envp, count);
	if (first == NULL)
		return (NULL);
	count++;
	while (envp[count] != NULL)
	{
		env = get_env_type_value(envp, count);
		if (env == NULL)
			return (free_env(first));
		ft_lstenv_back(&first, env);
		count++;
	}
	return (get_env2(first));
}

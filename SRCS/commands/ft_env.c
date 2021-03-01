#include "../shell_header.h"

void	ft_env(t_env *env, int fd)
{
	while (env != NULL)
	{
		if (env->class == 1)
		{
			ft_putstr_fd(env->type, fd);
			ft_putstr_fd("=", fd);
			if (env->value != NULL)
				ft_putstr_fd(env->value, fd);
			ft_putchar_fd('\n', fd);
		}
		env = env->next;
	}
}

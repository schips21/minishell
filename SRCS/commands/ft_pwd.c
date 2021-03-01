#include "../shell_header.h"

int		ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (errno != 0)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	ft_putendl_fd(pwd, 1);
	if (pwd)
		free(pwd);
	return (0);
}

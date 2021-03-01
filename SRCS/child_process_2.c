#include "shell_header.h"

char		*ft_def_strdup(char *s1)
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

int			if_other_command(t_info *info)
{
	int		res;

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

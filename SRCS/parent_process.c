#include "shell_header.h"

int		parents_cmnd_exec(t_info *info, t_env *env, t_general *general)
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
		ft_exit(info, general);
	return (res);
}

int		if_parent_process(t_info *info, t_general *general)
{
	int res;

	res = 0;
	if (ft_strncmp(info->args[0], "cd", 3) == 0)
		res = 1;
	else if (ft_strncmp(info->args[0], "export", 7) == 0 &&
			info->args[1] != NULL)
		res = 1;
	else if (ft_strncmp(info->args[0], "unset", 6) == 0)
		res = 1;
	else if ((ft_strncmp(info->args[0], "exit", 5) == 0) &&
			general->other_command == 0)
	{
		res = 1;
	}
	return (res);
}

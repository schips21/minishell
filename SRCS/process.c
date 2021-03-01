#include "shell_header.h"

void	pipe_error(t_general *general, t_info *info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(info->args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	general->other_command = -1;
}

void	pipe_classification_2(t_general *general, t_info *info)
{
	if (general->prev_pipe == 1 && info->pipe == 0)
	{
		if (general->pipe_fd2[0] == -2 && general->pipe_fd2[1] == -2)
			general->other_command = 2;
		else
			general->other_command = 4;
		general->prev_pipe = 0;
	}
	else if (general->prev_pipe == 1 && info->pipe == 1)
	{
		if (general->pipe_fd2[0] == -2 && general->pipe_fd2[1] == -2)
		{
			general->other_command = 3;
			if (pipe(general->pipe_fd2) < 0)
				pipe_error(general, info);
		}
		else
		{
			general->other_command = 6;
			if (pipe(general->pipe_fd) < 0)
				pipe_error(general, info);
		}
		general->prev_pipe = 1;
	}
}

void	pipe_classification_1(t_general *general, t_info *info)
{
	general->prev_pipe = 1;
	if (pipe(general->pipe_fd) < 0)
		pipe_error(general, info);
	general->other_command = 1;
}

int		process(t_env *env, t_info *info, t_general *general)
{
	int	res;

	res = 0;
	if (info->args == NULL)
	{
		redirect_processing(info);
		return (g_res);
	}
	general->other_command = 0;
	if (info->pipe == 1 && general->prev_pipe != 1)
		pipe_classification_1(general, info);
	else
		pipe_classification_2(general, info);
	if (general->other_command < 0)
		return (errno);
	res = command_execution(info, env, general);
	return (res);
}

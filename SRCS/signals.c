#include "shell_header.h"

void	listener(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		write(1, "minishell: ", 11);
		if (g_ctrl_d == 1)
			g_ctrl_d = 2;
		g_res = 1;
	}
	else if (signal == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

int		signals_in_parent(int stat, t_general *general)
{
	if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == 2)
			stat = 130;
		else if (WTERMSIG(stat) == 3)
			stat = 131;
		general->flag = 1;
	}
	else
		stat = WEXITSTATUS(stat);
	signal(SIGINT, listener);
	signal(SIGQUIT, listener);
	return (stat);
}

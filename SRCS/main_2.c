#include "shell_header.h"

int			error_errno_no_info(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	exit(errno);
}

t_general	*fullfill_general(void)
{
	int			*fd;
	int			*fd2;
	t_general	*general;

	fd = NULL;
	if (!(general = malloc(sizeof(t_general *))))
		return (NULL);
	if (!(fd = malloc(sizeof(int *) * 2)))
		error_errno_no_info();
	fd[0] = -2;
	fd[1] = -2;
	general->pipe_fd = fd;
	if (!(fd2 = malloc(sizeof(int *) * 2)))
		error_errno_no_info();
	fd2[0] = -2;
	fd2[1] = -2;
	general->pipe_fd2 = fd2;
	general->flag = 0;
	return (general);
}

void		main_init_gnl(int *i, t_info *parsed, t_general *general)
{
	*i = 1;
	ft_bzero(parsed, sizeof(*parsed));
	general->prev_pipe = 0;
	general->pipe_fd2[0] = -2;
	general->pipe_fd2[1] = -2;
	general->pipe_fd[0] = -2;
	general->pipe_fd[1] = -2;
}

char		*check_free_line(char *line, int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	if (line)
	{
		free(line);
		line = NULL;
	}
	g_ctrl_d = 0;
	return (line);
}

void		dup_after_redir(t_info *info, int dup_in, int dup_out,
			t_general *gen)
{
	if (info->right_redir == 1)
	{
		dup2(dup_out, 1);
		info->right_redir = 0;
	}
	if (g_res == 130 && gen->flag == 1)
	{
		gen->flag = 0;
		write(1, "\n", 1);
	}
	else if (g_res == 131 && gen->flag == 1)
	{
		gen->flag = 0;
		ft_putendl_fd("^\\Quit: 3", 1);
	}
	if (info->left_redir == 1)
	{
		dup2(dup_in, 0);
		info->left_redir = 0;
	}
	main_free_args_redirs(info, 0);
	g_ctrl_d = 0;
}

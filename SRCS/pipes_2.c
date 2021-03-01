#include "shell_header.h"

void	last_after_odd_pipe(t_general *general)
{
	close(general->pipe_fd[1]);
	dup2(general->pipe_fd[0], 0);
	close(general->pipe_fd[0]);
}

void	last_after_even_pipe(t_general *general)
{
	close(general->pipe_fd2[1]);
	dup2(general->pipe_fd2[0], 0);
	close(general->pipe_fd2[0]);
}

void	middle_after_odd_pipe(t_general *general)
{
	close(general->pipe_fd[1]);
	dup2(general->pipe_fd[0], 0);
	close(general->pipe_fd[0]);
	general->pipe_fd[0] = -2;
	general->pipe_fd[1] = -2;
}

void	middle_after_even_pipe(t_general *general)
{
	close(general->pipe_fd2[1]);
	dup2(general->pipe_fd2[0], 0);
	close(general->pipe_fd2[0]);
	general->pipe_fd2[0] = -2;
	general->pipe_fd2[1] = -2;
}

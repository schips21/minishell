#include "shell_header.h"

void	pipe_execution(t_general *general, t_info *info)
{
	if (general->other_command == 2 && info->left_redir == 0)
		last_after_odd_pipe(general);
	else if (general->other_command == 3 && info->left_redir == 0)
		middle_after_odd_pipe(general);
	else if (general->other_command == 6 && info->left_redir == 0)
		middle_after_even_pipe(general);
	else if (general->other_command == 4 && info->left_redir == 0)
		last_after_even_pipe(general);
}

void	pipe_execution_child(t_general *general, t_info *info)
{
	if ((general->other_command == 1 || general->other_command == 6) &&
		info->right_redir == 0)
	{
		close(general->pipe_fd[0]);
		dup2(general->pipe_fd[1], 1);
		close(general->pipe_fd[1]);
	}
	else if (general->other_command == 3 && info->right_redir == 0)
	{
		close(general->pipe_fd2[0]);
		dup2(general->pipe_fd2[1], 1);
		close(general->pipe_fd2[1]);
	}
	errno = 0;
}

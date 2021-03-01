#include "shell_header.h"

int				command_execution(t_info *info, t_env *env, t_general *general)
{
	int			res;
	pid_t		pid;
	int			stat;

	errno = 0;
	if ((res = redirect_processing(info)) != 0)
		return (res);
	if (if_parent_process(info, general))
		return (parents_cmnd_exec(info, env, general));
	pipe_execution(general, info);
	pid = fork();
	if (pid < 0)
		return (error_errno(info));
	else if (pid == 0)
		execution_child(info, env, general);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &stat, WUNTRACED);
	return (signals_in_parent(stat, general));
}

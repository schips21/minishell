#include "shell_header.h"

void		main_utils(t_info *parsed)
{
	int tmp;
	int tmp_pipe;

	tmp = parsed->cur_i;
	tmp_pipe = parsed->pipe_prev;
	ft_bzero(parsed, sizeof(*parsed));
	parsed->cur_i = tmp;
	parsed->pipe_prev = tmp_pipe;
}

void		main_bef_proc(t_general *gen, int in, int out)
{
	if (gen->prev_pipe == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
	}
}

void		main_pars(t_env *env, t_info *parsed, int *i)
{
	*i = parser(g_line, parsed, env);
	if (*i == -1)
	{
		free(parsed->args);
		parsed->args = NULL;
		*i = 0;
	}
}

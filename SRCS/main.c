#include "shell_header.h"

void		minishell_signal(t_info *parsed)
{
	parsed->flag = 0;
	signal(SIGINT, listener);
	signal(SIGQUIT, listener);
}

void		minishell_to_null(t_info *parsed)
{
	parsed->cur_i = 0;
	parsed->pipe_prev = 0;
}

void		minishell(t_env *env, t_general *general, int in, int out)
{
	t_info		parsed;
	int			i;

	minishell_to_null(&parsed);
	while (get_next_line(0, &g_line))
	{
		minishell_signal(&parsed);
		if (g_ctrl_d == 2)
		{
			check_free_line(g_line, in, out);
			continue ;
		}
		main_init_gnl(&i, &parsed, general);
		while (i != 0)
		{
			main_utils(&parsed);
			if (parser_check_line(g_line, 0) == 1)
				break ;
			main_pars(env, &parsed, &i);
			main_bef_proc(general, in, out);
			g_res = process(env, &parsed, general);
			dup_after_redir(&parsed, in, out, general);
		}
		check_free_line(g_line, in, out);
	}
}

int			main(int argc, char **argv, char *envp[])
{
	t_general	*general;
	t_env		*env;
	int			dup_in;
	int			dup_out;

	if (argc == -2 && !argv)
		return (0);
	env = NULL;
	env = get_env(envp, env);
	signal(SIGINT, listener);
	signal(SIGQUIT, listener);
	general = fullfill_general();
	dup_in = dup(0);
	dup_out = dup(1);
	dup2(dup_in, 0);
	dup2(dup_out, 1);
	general->dup_in = dup_in;
	general->dup_out = dup_out;
	minishell(env, general, dup_in, dup_out);
	dup2(dup_in, 0);
	dup2(dup_out, 1);
	free(env);
	free_general(general);
	return (0);
}

void		pre_gnl(void)
{
	g_ctrl_d = 0;
	write(1, "minishell: ", 11);
}

#include "shell_header.h"

t_general		*fullfill_general()
{
	int			*fd;
	t_general	*general;

	fd = NULL;
	general = NULL;
	general = malloc(sizeof(t_general *));
	if (general == NULL)
		return (NULL);
	fd = malloc(sizeof(int *) * 2);
	if (fd == NULL)
	{
		free(general);
		return (NULL);
	}
	fd[0] = -2;
	fd[1] = -2;
	general->pipe_fd = fd;
	return (general);
}

int main(int argc, char **argv, char *envp[])
{
	t_info parsed;
	t_general	*general;
	int i;
	int tmp;
	int tmp_pipe;
	int j;
	t_env	*env;
	int dup_in;
	int dup_out;

	char *line = NULL;
	env = NULL;
	env = get_env(envp, env);
	signal(SIGQUIT, SIG_IGN);
	general = fullfill_general();
	if (general == NULL)
		return (-1);
	dup_in = dup(0);//dup
	dup_out = dup(1);//dup
	dup2(dup_in, 0);//dup
	dup2(dup_out, 1);//dup
	general->dup_in = dup_in;//dup
	general->dup_out = dup_out;//dup
	
	if (argc == -2 && !argv)
		return (0);
	parsed.cur_i = 0;
	parsed.pipe_prev = 0;
	while (get_next_line(0, &line))
	{
		i = 1;
		ft_bzero(&parsed, sizeof(parsed));
		general->pipe_in_prev_command = 0;
		while(i != 0)
		{
			tmp = parsed.cur_i;
			tmp_pipe = parsed.pipe_prev;
			ft_bzero(&parsed, sizeof(parsed));
			parsed.cur_i = tmp;
			parsed.pipe_prev = tmp_pipe;
			if (parser_check_line(line, &parsed) == 1)
				break;
			i = parser(line, &parsed, env);
			parsed.in = 0;
			parsed.out = 1;
			parsed.envp = envp;
			if (i == -1)
			{
				free(parsed.args);
				parsed.args = NULL;
				i = 0;
			}
			g_res = process(env, &parsed, general);//process
			if (parsed.args)
			{
				j = 0;
				while (parsed.args[j])
					free(parsed.args[j++]);
				free(parsed.args);
			}
			if (parsed.redirs)
			{
				j = 0;
				while (parsed.redirs[j])
					free(parsed.redirs[j++]);
				free(parsed.redirs);
			}
		}
		dup2(dup_in, 0);//dup
		dup2(dup_out, 1);//dup
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	dup2(parsed.dup_in, 0);//dup reverse
	dup2(parsed.dup_out, 1);//dup reverse
	free(env);
	return (0);
}

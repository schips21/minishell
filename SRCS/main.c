#include "shell_header.h"

int main(int argc, char **argv, char *envp[])
{
	t_info parsed;
	int i;
	int tmp;
	int j;
	t_env	*env;

	char *line = NULL;
	env = NULL;
	env = get_env(envp, env);
	signal(SIGQUIT, SIG_IGN);
	if (argc == -2 && !argv)
		return (0);
	while (get_next_line(0, &line))
	{
		i = 1;
		ft_bzero(&parsed, sizeof(parsed));
		while(i != 0)
		{
			tmp = parsed.cur_i;
			ft_bzero(&parsed, sizeof(parsed));
			parsed.cur_i = tmp;
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
			g_res = process(env, &parsed);
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
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	free(env);
	return (0);
}
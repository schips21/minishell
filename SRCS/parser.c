#include "shell_header.h"

//Обработать доллар в двойных кавычках

int		parser(char *line, t_info *parsed, t_env *env)
{
	int i;
	int arg_i;

	i = parsed->cur_i;
	while (!ft_strchr(";|", line[i]) && line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			break;
		arg_i = new_word(parsed);
		while (!ft_strchr(" ;|", line[i]) && line[i])
		{
			if (line[i] == '>' || line[i] == '<')
				parser_redir(line, parsed, &i);
			else if (line[i] == '\'')
			{
				i++;
				while (line[i] != '\'')
					new_letter(parsed, arg_i, line[i++]);
				i++;
			}
			else if (line[i] == '\"')
				two_quot(line, parsed, arg_i, &i);
			else if (line[i] == '$')
				pars_dollar_env(parsed, env, arg_i, pars_dollar(line, &i));
			else if (line[i] == '\\')
			{
				i++;
				new_letter(parsed, arg_i, line[i++]);
			}
			else
				new_letter(parsed, arg_i, line[i++]);
		}
		arg_i++;
	}
	if (!parsed->args || !parsed->args[0])
		return (0);
	count_args(parsed);
	if (ft_strncmp(parsed->args[0], "echo", 4) == 0 && parsed->args_num > 0)
		parse_echo_n(parsed);
	parsed->cur_i = i;
	if (line[i] == '|')
		parsed->pipe = 1;
	if (line[i] == '\0')
		return (0);
	parsed->cur_i++;
	return (1);
}

int main(int argc, char **argv, char *envp[])
{
	t_info parsed;
	int i;
	int tmp;
	int j;
//	char *line = "cd -; pwd $PWD";
	char *line = NULL;
	parsed.cur_i = 0;

	t_env	*env;
	env = NULL;
	env = get_env(envp, env);

	if (argc == -2 && !argv)
		return (0);

	while (get_next_line(0, &line))
{

		i = 1;
	ft_bzero(&parsed, sizeof(parsed));
		while(i != 0)
	{
//		env = get_env(envp, env);
		tmp = parsed.cur_i;
		ft_bzero(&parsed, sizeof(parsed));
		parsed.cur_i = tmp;
		i = parser(line, &parsed, env);
		parsed.in = 0;
		parsed.out = 1;
		parsed.envp = envp;
//		process(env, &parsed);

		if (parsed.args)
		{
			printf("%s%d%s\n", "THERE ARE ", parsed.args_num, " ARGS");
			printf("%s%s\n", "TYPE IS: ", parsed.args[0]);
			if (parsed.n_flag == 1)
				printf("%s\n", "ECHO HAS -n FLAG");
			j = 1;
			while (parsed.args[j])
			{
				printf("%s%d%s%s\n", "ARG ", j - 1, " IS: ", parsed.args[j]);
				j++;
			}
			j = 0;
			while (parsed.args[j])
				free(parsed.args[j++]);
			free(parsed.args);
		}
		if (parsed.redirs)
		{
			printf("%s\n", "REDIRECTS ARE:");
			j = 0;
			while (parsed.redirs[j])
				printf("%s\n", parsed.redirs[j++]);
			j = 0;
			while (parsed.redirs[j])
				free(parsed.redirs[j++]);
			free(parsed.redirs);
		}
		printf("%s%d\n\n", "PIPE IS: ", parsed.pipe);

	}
	if(line)
	{
		free(line);
		line = NULL;
	}

	}
	free(env);
	return (0);
}

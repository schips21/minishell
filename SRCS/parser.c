#include "shell_header.h"

int		parser(char *line, t_info *parsed, t_env *env)
{
	int i;
	int j;
	int arg_i;
	char *res_prev_str;

	parser_check_line(line, &parsed);
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
			{
				parsed->arg_i = arg_i;
				two_quot(line, parsed, &i, env);
			}
			else if (line[i] == '$')
			{
				if (line[i + 1] == '?')
				{
					i += 2;
					res_prev_str = ft_itoa(g_res);
					j = 0;
					while (res_prev_str[j] != '\0')
						new_letter(parsed, arg_i, res_prev_str[j++]);
					if (res_prev_str)
						free(res_prev_str);
				}
				else if (line[i + 1] == '\'' || line[i + 1] == '\"')
					i++;
				else
					pars_dollar_env(parsed, env, arg_i, pars_dollar(line, &i));
			}
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
		return (-1);
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

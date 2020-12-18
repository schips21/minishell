#include "shell_header.h"

void	two_quot(char *line, t_info *parsed, int arg_i, int *i)
{
	(*i)++;
	while (line[*i] != '\"')
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\\' || line[*i + 1] == '\"' || line[*i + 1] == '$'))
		{
			(*i)++;
			new_letter(parsed, arg_i, line[(*i)++]);
		}

//		else if (line[i] == '$')
//		условие про доллар
		else
			new_letter(parsed, arg_i, line[(*i)++]);
	}
	(*i)++;
}

void	parse_echo_n(t_info *parsed)
{
	int i;

	i = 0;
	if (parsed->args[1][i] == '-')
	{
		i++;
		while (parsed->args[1][i] == 'n' && parsed->args[1][i] != '\0')
			i++;
		if (parsed->args[1][i] == '\0')
			parsed->n_flag = 1;
	}
	if (parsed->n_flag == 1)
	{
		make_type(parsed, 1);
		parsed->args_num--;
	}
}

void	count_args(t_info *parsed)
{
	int i;

	i = 0;
	if (parsed->args)
	{
		if (parsed->args[0] == NULL)
		{
			free(parsed->args[0]);
			free(parsed->args);
			parsed->args = NULL;
		}
		else
		{
			while(parsed->args[i++])
				parsed->args_num++;
//			удаляем команду из счетчика
			parsed->args_num--;
		}
	}
}

#include "shell_header.h"

int		parser_check_line_skip_quot(char *line, int *i, t_line_check *l_check)
{
	(*i)++;
	while (!(line[*i] == '\"' && line[*i - 1] != '\\') && line[*i] != '\0')
	{
		l_check->symb++;
		(*i)++;
	}
	if (line[*i] == '\0')
		return (1);
	return (0);
}

int		parser_check_line_skip_q_one(char *line, int *i, t_line_check *l_check)
{
	(*i)++;
	while (!(line[*i] == '\'' && line[*i - 1] != '\\') && line[*i] != '\0')
	{
		l_check->symb++;
		(*i)++;
	}
	if (line[*i] == '\0')
		return (1);
	return (0);
}

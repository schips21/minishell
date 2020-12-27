#include "shell_header.h"

void	parser_check_line_skip_quot(char *line, int *i, t_line_check *line_check)
{
	(*i)++;
	while (!(line[*i] == '\"' && line[*i - 1] != '\\') && line[*i] != '\0')
	{
		line_check->symb++;
		(*i)++;
	}
}

void	parser_check_line_skip(char *line, int *i, t_line_check *line_check)
{
	if (line[*i] == '\\')
	{
		line_check->symb++;
		(*i)++;
	}
	if (line[*i] == '\"')
		parser_check_line_skip_quot(line, i, line_check);
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (!(line[*i] == '\'' && line[*i - 1] != '\\') && line[*i] != '\0')
		{
			line_check->symb++;
			(*i)++;
		}
	}
	else if (line[*i] == ' ')
		line_check->space++;
	else
		line_check->symb++;
	(*i)++;
}

int		parser_check_line_ret(t_info *info)
{
	info->res_prev = 258;
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 1);
	return (1);
}

void	parser_check_line_util(char *line, t_line_check *line_check, int *i)
{
	ft_bzero(line_check, sizeof(*line_check));
	while (!ft_strchr(";|><", line[*i]) && line[*i] != '\0')
		parser_check_line_skip(line, i, line_check);
}

int		parser_check_line(char *line, t_info *info)
{
	int i;
	t_line_check line_check;

	i = 0;
	while (line[i] != '\0')
	{
		parser_check_line_util(line, &line_check, &i);
		if ((line[i] == ';' || line[i] == '|') && line_check.symb == 0)
			return (parser_check_line_ret(info));
		else if (line[i] == '|' || line[i] == '<')
		{
			i++;
			parser_check_line_util(line, &line_check, &i);
			if (line_check.symb == 0)
				return (parser_check_line_ret(info));
		}
		else if (line[i] == '>')
		{
			i++;
			if (line[i] == '>')
				i++;
			parser_check_line_util(line, &line_check, &i);
			if (line_check.symb == 0)
				return (parser_check_line_ret(info));
		}
		i++;
	}
	return (0);
}

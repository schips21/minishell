#include "shell_header.h"

void	parser_check_line(char *line, t_info *info)
{
	int i;
	t_line_check line_check;

	i = 0;
	ft_bzero(&line_check, sizeof(line_check));
	while (line[i] != '\0')
	{
		while (!ft_strchr(";|><", line[i]) && line[i] != '\0')
		{
			if (line[i] == ' ')
				line_check.space++;
			else
				line_check.symb++;
			i++;
		}
		if (line[i] == ';')
		{
			if (line_check.symb == 0)
			{
				info->res_prev = 258;
				ft_putstr_fd("minishell: syntax error near unexpected token `;'", 1);
				exit(info->res_prev);
			}
			i++;
		}
	}
}
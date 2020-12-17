#include "shell_header.h"

int 	check_quot

int 	parser_redir(char *line, t_info *parsed, int *i, int end)
{
	int j; //счетчик для строки, который не меняется в исходной функции

	j = *i;
	if (line[j] == '>' && line[j + 1] != '>')
	{
		if (!(parsed->redir[parsed->redir_utils->cur_i] = malloc(sizeof(char) * 2)))
			return (0);
		parsed->redir[parsed->redir_utils->cur_i][0] = '>';
		parsed->redir[parsed->redir_utils->cur_i][1] = '\0';
		j++;
	}
	else if (line[j] == '>' && line[j + 1] == '>')
	{
		if (!(parsed->redir[parsed->redir_utils->cur_i] = malloc(sizeof(char) * 3)))
			return (0);
		parsed->redir[parsed->redir_utils->cur_i][0] = '>';
		parsed->redir[parsed->redir_utils->cur_i][1] = '>';
		parsed->redir[parsed->redir_utils->cur_i][2] = '\0';
		j += 2;
	}
	else
	{
		if (!(parsed->redir[parsed->redir_utils->cur_i] = malloc(sizeof(char) * 2)))
			return (0);
		parsed->redir[parsed->redir_utils->cur_i][0] = '<';
		parsed->redir[parsed->redir_utils->cur_i][1] = '\0';
		j++;
	}
	parsed->redir_utils->cur_i++;
	while (line[j] == ' ')
		j++;
	*i = j;
}
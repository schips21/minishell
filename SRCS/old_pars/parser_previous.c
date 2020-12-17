#include "shell_header.h"

void 	pars_args(char *line, t_info *parsed)
{
	parsed->args = ft_split(line, ' ');
}

void	pars_echo(char *line, t_info *parsed)
{
	int i;

	parsed->type = ft_strdup("echo");
	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp((line + i), "-n", 2) == 0)
	{
		parsed->n_flag = 1;
		i += 2;
	}
	pars_args((line + i), parsed);
	i = 0;
	while (parsed->args[i++] != NULL)
		parsed->args_num++;
	parsed->next;
}

void	parser(char *line, t_info *parsed)
{

	if (ft_strncmp(line, "echo ", 5) == 0)
		pars_echo(line + 5, parsed);

}

int main()
{
	t_info parsed;
	char *line = "echo   -n lflf blbl";

	ft_bzero(&parsed, sizeof(parsed));
	parser(line, &parsed);
	printf("%s\n%s\n%s\n", parsed.type, parsed.args[0], parsed.args[1]);
	return (0);
}
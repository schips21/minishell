#include "shell_header.h"

int		gnl_return(char **residue, char **line, int count)
{
	if (residue[0] == NULL)
		return (0);
	else if (count < 0)
		return (error_pr(NULL, residue));
	else
		return (after_reading(residue, line));
}

int		gnl_exit(void)
{
	ft_putstr_fd("  \b\b", 2);
	ft_putstr_fd("exit", 2);
	exit(0);
}

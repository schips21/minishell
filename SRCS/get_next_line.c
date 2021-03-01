#include "shell_header.h"

size_t			ft_strlen_sp(char *str, char sp)
{
	size_t		i;

	i = 0;
	while (str[i] != sp)
		i++;
	return (i);
}

int				error_pr(char **line, char **residue)
{
	if (**line)
	{
		free(*line);
		*line = NULL;
	}
	if (residue[0])
	{
		free(residue[0]);
		residue[0] = NULL;
	}
	return (-1);
}

int				after_reading(char **residue, char **line)
{
	char		*x;
	char		*tmp;

	if ((x = ft_strchr_gnl(residue[0], '\n')))
	{
		if (!(*line = ft_strdup_sp(residue[0], '\n')))
			return (error_pr(NULL, residue));
		if (!(tmp = ft_strdup_sp(&x[1], '\0')))
			return (error_pr(line, residue));
		free(residue[0]);
		residue[0] = tmp;
		tmp = NULL;
		x = NULL;
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup_sp(residue[0], '\0')))
			return (error_pr(NULL, residue));
		free(residue[0]);
		residue[0] = NULL;
		return (0);
	}
}

int				lining(char **residue, char **line, char *x)
{
	char		*tmp;

	if (!(*line = ft_strdup_sp(residue[0], '\n')))
		return (error_pr(NULL, residue));
	if (!(tmp = ft_strdup_sp(&x[1], '\0')))
		return (error_pr(line, residue));
	free(residue[0]);
	residue[0] = tmp;
	tmp = NULL;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	int			count;
	static char	*residue[256];
	char		buffer[BUFFER_SIZE + 1];

	pre_gnl();
	if (line == NULL || (count = read(fd, buffer, 0) < 0))
		return (-1);
	buffer[0] = '\0';
	while ((count = read(fd, buffer, BUFFER_SIZE)) >= 0)
	{
		if (count == 0 && buffer[0] != '\0')
		{
			ft_putstr_fd("  \b\b", 2);
			buffer[1] = '\0';
			g_ctrl_d = 1;
			continue;
		}
		else if (count == 0)
			gnl_exit();
		if (joining(buffer, count, residue) == -1)
			return (-1);
		if ((ft_strchr_gnl(residue[0], '\n')))
			return (lining(residue, line, ft_strchr_gnl(residue[0], '\n')));
	}
	return (gnl_return(residue, line, count));
}

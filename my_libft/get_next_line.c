/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/10/16 05:43:57 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	int			flag;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0
			|| (count = read(fd, buffer, 0) < 0))
		return (-1);
	flag = 0;
	while ((count = read(fd, buffer, BUFFER_SIZE)) > 0 || flag == 0)
	{
		flag++;
		if (joining(buffer, count, residue) == -1)
			return (-1);
		if ((ft_strchr_gnl(residue[0], '\n')))
			return (lining(residue, line, ft_strchr_gnl(residue[0], '\n')));
	}
	if (residue[0] == NULL)
		return (0);
	else if (count < 0)
		return (error_pr(NULL, residue));
	else
		return (after_reading(residue, line));
}

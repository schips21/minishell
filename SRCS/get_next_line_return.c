/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_return.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 13:08:12 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

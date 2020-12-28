/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_check_d.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/10/16 05:43:57 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	ft_putstr_fd("minishell$ exit", 2);
	exit(0);
}

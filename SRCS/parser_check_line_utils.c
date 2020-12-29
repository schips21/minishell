/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_line_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schips <schips@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:43:36 by schips            #+#    #+#             */
/*   Updated: 2020/12/29 21:43:37 by schips           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

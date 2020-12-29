/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schips <schips@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:21:56 by schips            #+#    #+#             */
/*   Updated: 2020/12/28 22:21:59 by schips           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

int		parser_check_line_skip(char *line, int *i, t_line_check *line_check)
{
	if (line[*i] == '\\')
	{
		line_check->symb++;
		(*i)++;
	}
	if (line[*i] == '\"')
	{
		if ((parser_check_line_skip_quot(line, i, line_check)) == 1)
			return (1);
	}
	else if (line[*i] == '\'')
	{
		if ((parser_check_line_skip_q_one(line, i, line_check)) == 1)
			return (1);
	}
	else if (line[*i] == ' ')
		line_check->space++;
	else
		line_check->symb++;
	(*i)++;
	return (0);
}

int		parser_check_line_ret(void)
{
	g_res = 258;
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 1);
	return (1);
}

int		parser_check_line_util(char *line, t_line_check *line_check, int *i)
{
	ft_bzero(line_check, sizeof(*line_check));
	while (!ft_strchr(";|><", line[*i]) && line[*i] != '\0')
	{
		if ((parser_check_line_skip(line, i, line_check)) == 1)
			return (1);
	}
	return (0);
}

int		parser_check_l_red(char *l, t_info *info, int *i, t_line_check *l_check)
{
	(*i)++;
	if (l[*i] == '>')
		(*i)++;
	if ((parser_check_line_util(l, l_check, i)) == 1)
		return (1);
	if (l_check->symb == 0)
		return (1);
	return (0);
}

int		parser_check_line(char *line, t_info *info, int i)
{
	t_line_check	line_check;

	while (line[i] != '\0')
	{
		if ((parser_check_line_util(line, &line_check, &i)) == 1)
			return (parser_check_line_ret());
		if ((line[i] == ';' || line[i] == '|') && line_check.symb == 0)
			return (parser_check_line_ret());
		else if (line[i] == '|' || line[i] == '<')
		{
			i++;
			if ((parser_check_line_util(line, &line_check, &i)) == 1)
				return (parser_check_line_ret());
			if (line_check.symb == 0 && !(line[i] == '>' || line[i] == '<'))
				return (parser_check_line_ret());
		}
		else if (line[i] == '>')
		{
			if ((parser_check_l_red(line, info, &i, &line_check)) == 1)
				return (parser_check_line_ret());
		}
		if (line[i] != '\0')
			i++;
	}
	return (0);
}

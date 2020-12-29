/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schips <schips@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:38:42 by schips            #+#    #+#             */
/*   Updated: 2020/12/29 21:47:36 by schips           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

void	two_quot(char *line, t_info *parsed, int *i, t_env *env)
{
	(*i)++;
	if (line[*i] == '\"')
	{
		new_letter(parsed, parsed->arg_i, '\0');
	}
	while (line[*i] != '\"')
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\\' ||
		line[*i + 1] == '\"' || line[*i + 1] == '$'))
		{
			(*i)++;
			new_letter(parsed, parsed->arg_i, line[(*i)++]);
		}
		else if (line[*i] == '$')
			pars_dollar_env(parsed, env, parsed->arg_i, pars_dollar(line, i));
		else
			new_letter(parsed, parsed->arg_i, line[(*i)++]);
	}
	(*i)++;
}

void	parse_n_while(t_info *parsed, int i, int *fl_n)
{
	if (parsed->args[1][i] == '-')
	{
		i++;
		if (parsed->args[1][i] == 'n')
		{
			while (parsed->args[1][i] == 'n' &&
			parsed->args[1][i] != '\0')
				i++;
			if (parsed->args[1][i] == '\0')
			{
				make_type(parsed);
				parsed->args_num--;
			}
			else
				*fl_n = 0;
		}
		else
			*fl_n = 0;
	}
	else
		*fl_n = 0;
}

void	parse_echo_n(t_info *parsed)
{
	int i;
	int fl_n;

	i = 0;
	fl_n = 1;
	if (parsed->args[1][i] == '-')
	{
		i++;
		if (parsed->args[1][i] == 'n')
		{
			while (parsed->args[1][i] == 'n' && parsed->args[1][i] != '\0')
				i++;
			if (parsed->args[1][i] == '\0')
				parsed->n_flag = 1;
		}
	}
	if (parsed->n_flag == 1)
	{
		make_type(parsed);
		parsed->args_num--;
		while (fl_n == 1 && parsed->args[1])
			parse_n_while(parsed, 0, &fl_n);
	}
}

void	count_args(t_info *parsed)
{
	int i;

	i = 0;
	if (parsed->args)
	{
		if (parsed->args[0] == NULL)
		{
			free(parsed->args[0]);
			free(parsed->args);
			parsed->args = NULL;
		}
		else
		{
			while (parsed->args[i++])
				parsed->args_num++;
			parsed->args_num--;
		}
	}
}

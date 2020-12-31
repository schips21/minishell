/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:39:42 by schips            #+#    #+#             */
/*   Updated: 2020/12/31 16:21:10 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

int		parser_return(char *line, t_info *parsed, int i)
{
	parsed->in = 0;
	parsed->out = 1;
	if (!parsed->args || !parsed->args[0])
		return (-1);
	count_args(parsed);
	if (ft_strncmp(parsed->args[0], "echo", 4) == 0 &&
		parsed->args_num > 0)
		parse_echo_n(parsed);
	parsed->cur_i = i;
	if (line[i] == '|')
		parsed->pipe = 1;
	if (line[i] == '\0')
		return (0);
	parsed->cur_i++;
	return (1);
}

void	parser_dollar_start(char *line, t_info *parsed, t_env *env, int *i)
{
	char	*res_prev_str;
	int		j;

	if (line[*i + 1] == '?')
	{
		*i += 2;
		res_prev_str = ft_itoa(g_res);
		j = 0;
		while (res_prev_str[j] != '\0')
			new_letter(parsed, parsed->arg_i, res_prev_str[j++]);
		if (res_prev_str)
			free(res_prev_str);
	}
	else if (line[*i + 1] == '\'' || line[*i + 1] == '\"')
		(*i)++;
	else
		pars_dollar_env(parsed, env, parsed->arg_i, pars_dollar(line, i));
}

void	parser_spec(char *line, t_info *parsed, t_env *env, int *i)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		if (line[*i] == '\'')
			new_letter(parsed, parsed->arg_i, '\0');
		while (line[*i] != '\'')
			new_letter(parsed, parsed->arg_i, line[(*i)++]);
		(*i)++;
	}
	else if (line[*i] == '\"')
		two_quot(line, parsed, i, env);
	else if (line[*i] == '$')
		parser_dollar_start(line, parsed, env, i);
	else if (line[*i] == '\\')
	{
		(*i)++;
		new_letter(parsed, parsed->arg_i, line[(*i)++]);
	}
}

int		parser(char *line, t_info *parsed, t_env *env)
{
	int i;

	i = parsed->cur_i;
	while (!ft_strchr(";|", line[i]) && line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			break ;
		parsed->arg_i = new_word(parsed);
		while (!ft_strchr(" ;|", line[i]) && line[i])
		{
			if (line[i] == '>' || line[i] == '<')
				parser_redir(line, parsed, &i);
			else if (line[i] == '\'' || line[i] == '\"' ||
			line[i] == '$' || line[i] == '\\')
				parser_spec(line, parsed, env, &i);
			else
				new_letter(parsed, parsed->arg_i, line[i++]);
		}
		parsed->arg_i++;
	}
	return (parser_return(line, parsed, i));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mem_realloc_redir.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schips <schips@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:27:02 by schips            #+#    #+#             */
/*   Updated: 2020/12/28 22:27:03 by schips           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

int		new_word_next_red(t_info *parsed, int i, int j)
{
	char	**new;

	while (parsed->redirs[i])
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 2))))
		return (0);
	new[i] = NULL;
	new[i + 1] = NULL;
	while (j < i)
	{
		new[j] = parsed->redirs[j];
		j++;
	}
	free(parsed->redirs);
	parsed->redirs = NULL;
	parsed->redirs = new;
	return (j);
}

int		new_word_red(t_info *parsed)
{
	if (!parsed->redirs)
	{
		if (!(parsed->redirs = malloc(sizeof(char *) * 2)))
			return (0);
		parsed->redirs[0] = NULL;
		parsed->redirs[1] = NULL;
		return (0);
	}
	else
		return (new_word_next_red(parsed, 0, 0));
}

int		new_letter_next_red(t_info *parsed, int red_i, char let)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(parsed->redirs[red_i]);
	if (!(new = malloc(sizeof(char) * (len + 2))))
		return (0);
	i = 0;
	while (parsed->redirs[red_i][i] != '\0')
	{
		new[i] = parsed->redirs[red_i][i];
		i++;
	}
	new[i] = let;
	new[i + 1] = '\0';
	free(parsed->redirs[red_i]);
	parsed->redirs[red_i] = new;
	return (i);
}

int		new_letter_red(t_info *parsed, int red_i, char let)
{
	if (!parsed->redirs[red_i])
	{
		if (!(parsed->redirs[red_i] = malloc(sizeof(char) * 2)))
			return (0);
		parsed->redirs[red_i][0] = let;
		parsed->redirs[red_i][1] = '\0';
		return (0);
	}
	else
		return (new_letter_next_red(parsed, red_i, let));
}

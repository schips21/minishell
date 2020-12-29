/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schips <schips@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:42:26 by schips            #+#    #+#             */
/*   Updated: 2020/12/29 21:59:22 by schips           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

t_general	*fullfill_general(void)
{
	int			*fd;
	int			*fd2;
	t_general	*general;

	fd = NULL;
	general = NULL;
	if (!(general = malloc(sizeof(t_general *))))
		return (NULL);
	if (!(fd = malloc(sizeof(int *) * 2)))
	{
		free(general);
		return (NULL);
	}
	fd[0] = -2;
	fd[1] = -2;
	general->pipe_fd = fd;
	if (!(fd2 = malloc(sizeof(int *) * 2)))
	{
		free(general);
		return (NULL);
	}
	fd2[0] = -2;
	fd2[1] = -2;
	general->pipe_fd2 = fd2;
	return (general);
}

void		free_general_info(t_general *general, t_info *info)
{
    //it's extremely not full
	free(general->pipe_fd);
	free(general->pipe_fd2);
	free(general);
	free(info);
}

void		listener(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		write(1, "minishell: ", 11);
	}
	else if (signal == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

void		main_init_gnl(int *i, t_info *parsed, t_general *general)
{
	*i = 1;
	ft_bzero(parsed, sizeof(*parsed));
	general->prev_pipe = 0;
	general->pipe_fd2[0] = -2;
	general->pipe_fd2[1] = -2;
	general->pipe_fd[0] = -2;
	general->pipe_fd[1] = -2;
}

void		main_free_args_redirs(t_info *parsed, int j)
{
	if (parsed->args)
	{
		j = 0;
		while (parsed->args[j])
			free(parsed->args[j++]);
		free(parsed->args);
	}
	if (parsed->redirs)
	{
		j = 0;
		while (parsed->redirs[j])
			free(parsed->redirs[j++]);
		free(parsed->redirs);
	}
}

int			main(int argc, char **argv, char *envp[])
{
	t_info parsed;
	t_general	*general;
	t_env	*env;
	int i;
	int tmp;
	int tmp_pipe;
	int dup_in;
	int dup_out;
	char *line;

	line = NULL;
	env = NULL;
	env = get_env(envp, env);
	signal(SIGINT, listener);
	signal(SIGQUIT, listener);
	general = fullfill_general();
	if (general == NULL)
		return (-1);
	dup_in = dup(0);
	dup_out = dup(1);
	dup2(dup_in, 0);
	dup2(dup_out, 1);
	general->dup_in = dup_in;
	general->dup_out = dup_out;
	if (argc == -2 && !argv)
		return (0);
	parsed.cur_i = 0;
	parsed.pipe_prev = 0;
	while (get_next_line(0, &line))
	{
		main_init_gnl(&i, &parsed, general);
		while (i != 0)
		{
			tmp = parsed.cur_i;
			tmp_pipe = parsed.pipe_prev;
			ft_bzero(&parsed, sizeof(parsed));
			parsed.cur_i = tmp;
			parsed.pipe_prev = tmp_pipe;
			if (parser_check_line(line, &parsed, 0) == 1)
				break ;
			i = parser(line, &parsed, env);
			parsed.in = 0;
			parsed.out = 1;
			parsed.envp = envp;
			if (i == -1)
			{
				free(parsed.args);
				parsed.args = NULL;
				i = 0;
			}
			g_res = process(env, &parsed, general);
			if (parsed.right_redir == 1)
			{
				dup2(dup_out, 1);
				parsed.right_redir = 0;
			}
			if (parsed.left_redir == 1)
			{
				dup2(dup_in, 0);
				parsed.left_redir = 0;
			}
			main_free_args_redirs(&parsed, 0);
		}
		dup2(dup_in, 0);
		dup2(dup_out, 1);
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	dup2(parsed.dup_in, 0);
	dup2(parsed.dup_out, 1);
	free(env);
	free_general_info(general, &parsed);
	return (0);
}

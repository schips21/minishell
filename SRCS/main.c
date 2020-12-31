/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:42:26 by schips            #+#    #+#             */
/*   Updated: 2020/12/31 17:17:25 by dskittri         ###   ########.fr       */
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
/*
char	*check_free_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (line);
}

void			dup_after_redir(t_info *info, int dup_in, int dup_out)
{
	if (info->right_redir == 1)
	{
		dup2(dup_out, 1);
		info->right_redir = 0;
	}
	if (g_res == 130 || g_res == 131)
		write(1, "\n", 1);
	if (info->left_redir == 1)
	{
		dup2(dup_in, 0);
		info->left_redir = 0;
	}
}

void			parser_tmp(t_info *parsed)
{
	int			tmp;
	int			tmp_pipe;

	tmp = parsed->cur_i;
	tmp_pipe = parsed->pipe_prev;
	ft_bzero(parsed, sizeof(parsed)); //все ли очищается? ft_bzero(&parsed, sizeof(parsed));
	parsed->cur_i = tmp;
	parsed->pipe_prev = tmp_pipe;
}

void			check_parser_i(int *i, t_info *parsed)
{
	if (*i == -1)
	{
		free(parsed->args);
		parsed->args = NULL;
		*i = 0;
	}
}

void			minishell(t_env *env, t_general *general, int in, int out)
{
	t_info		parsed;
	char		*line;
	int			i;

	line = NULL;
	while (get_next_line(0, &line))
	{
		main_init_gnl(&i, &parsed, general);
		while (i != 0)
		{
			parser_tmp(&parsed);
			if (parser_check_line(line, &parsed, 0) == 1)
				break ;
			i = parser(line, &parsed, env);
			printf("here\n");
			if (i == -1)
			{
				free(parsed.args);
				parsed.args = NULL;
				i = 0;
			}
			//check_parser_i(&i, &parsed);
			g_res = process(env, &parsed, general);
			dup_after_redir(&parsed, in, out);
									
			main_free_args_redirs(&parsed, 0);
			printf("here\n");
		}
		dup2(in, 0);
		dup2(out, 1);
		printf("here\n");
		line = check_free_line(line);
		printf("here\n");
	}
}

int				main(int argc, char **argv, char *envp[])
{
	t_general	*general;
	t_env		*env;
	int			dup_in;
	int			dup_out;

	if (argc == -2 && !argv)
		return (0);
	env = get_env(envp, env);
	signal(SIGINT, listener);
	signal(SIGQUIT, listener);
	general = fullfill_general();
	dup_in = dup(0);
	dup_out = dup(1);
	dup2(dup_in, 0);
	dup2(dup_out, 1);
	general->dup_in = dup_in;
	general->dup_out = dup_out;
	minishell(env, general, dup_in, dup_out);
	dup2(dup_in, 0);
	dup2(dup_out, 1);
	free(env);
	free_general(general);
	return (0);
}
*/


int			main(int argc, char **argv, char *envp[])
{
	t_info		parsed;
	t_general	*general;
	t_env		*env;

	
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
	g_ctrl_d = 0;
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
			if (g_ctrl_d == 1)
			{
				//очищение
				break;
			}
			g_res = process(env, &parsed, general);
			if (parsed.right_redir == 1)
			{
				dup2(dup_out, 1);
				parsed.right_redir = 0;
			}
			if (g_res == 130 || g_res == 131)
				write(1, "\n", 1);
			if (parsed.left_redir == 1)
			{
				dup2(dup_in, 0);
				parsed.left_redir = 0;
			}
			main_free_args_redirs(&parsed, 0);
			g_ctrl_d = 0;
			//printf("echo $? %i\n", g_res);
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
	free_general(general);
	return (0);
}

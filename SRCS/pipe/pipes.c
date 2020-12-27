/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:37:05 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/27 12:58:06 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"
/*
int			print_errors(int num)
{
	//0 - pipe_error
	//1 - fork error
	return (num - num - 1);
}

void         end_of_pipe(t_general *general)
{
    close(general->pipe_fd[0]);
    close(general->pipe_fd[1]);
    dup2(general->dup_in, 0);
    dup2(general->dup_out, 1);
}

int			pipe_read_only(t_info *info, t_env *env, t_general *general)
{
	//int		pid;
	int		res;	

	res = 0;
	if ((pid = fork()) < 0)
		return (print_errors(1));
	if (pid == 0)
	{
		printf("inside fork in read\n");
		close(general->pipe_fd[1]);
		dup2(general->pipe_fd[0], 0);
		close(general->pipe_fd[0]);
		command_execution(info, env);
		exit(0);
	}
    wait(NULL);
	ft_putendl_fd("general->dup_out", general->dup_out);
	ft_putendl_fd("1", 1);
	printf("%i\n", general->pipe_fd[0]);
	printf("%i\n", general->pipe_fd[1]);
	read_from_pipe(general->pipe_fd, info, env);
	ft_putendl_fd("general->dup_out", general->dup_out);
	ft_putendl_fd("1", 1);
	close(0);
	close(1);
    close(general->pipe_fd[0]);
    close(general->pipe_fd[1]);
    dup2(general->dup_in, 0);
    dup2(general->dup_out, 1);
	printf("after fork in read\n");
	//end_of_pipe(general);
	printf("End of pipe read only\n");
	return (res);
}

void		read_from_pipe(int *fd, t_info *info, t_env *env)
{
	int		pid;
	char	buffer[200];

	pid = fork();
	if (pid == 0)
	{
		printf("REad from pipe after\n");
		//close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		read(0, buffer, 200);
		printf("%s\n", buffer);
		ft_putstr_fd("__________________" , 1);
		printf("________________________\n");
		command_execution(info, env);
		//close(fd[1]);
		//command_execution(info, env);
		printf("REad from pipe after\n");
		exit(0);
	}
	printf("HELLO\n");
	printf("HELLO\n");
    wait(&pid);
	printf("HELLO\n");
	printf("HELLO\n");
}

int			pipe_write_only(t_info *info, t_env *env, t_general *general)
{
	int		fd[2];
	int		pid;
	int		res;

	printf("%i %i\n", general->dup_in, general->dup_out);
	res = 0;
	if ((pipe(fd)) == -1)
		return(print_errors(0));
	general->pipe_fd[0] = fd[0];
	general->pipe_fd[1] = fd[1];
	if ((pid = fork()) < 0)
		return (print_errors(1));
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		command_execution(info, env);
		exit(0);
	}
	wait(NULL);
	printf("End of pipe write only\n");
	//read_from_pipe(fd, info, env);
	//обработка вывода процесса выше
	return (res);
}*/
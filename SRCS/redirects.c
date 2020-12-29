/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schips <schips@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 13:02:44 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/29 21:46:06 by schips           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

void		redirect_processing_out(t_info *info, int i)
{
	if (info->out != 1)
		close(info->out);
	if (info->redirs[i][1] == '\0')
		info->out = open(info->redirs[i + 1], O_RDWR | O_TRUNC | O_CREAT,
		S_IREAD | S_IWRITE);
	else
		info->out = open(info->redirs[i + 1], O_RDWR | O_CREAT | O_APPEND,
		S_IREAD | S_IWRITE);
	if (info->out >= 0)
		dup2(info->out, 1);
	info->right_redir = 1;
}

void		redirect_processing_in(t_info *info, int i)
{
	if (info->in != 0)
		close(info->in);
	info->in = open(info->redirs[i + 1], O_RDWR);
	if (info->in >= 0)
		dup2(info->in, 0);
	info->left_redir = 1;
}

int			redirect_processing(t_info *info)
{
	int		i;

	i = 0;
	while (info->redirs != NULL && info->redirs[i] != NULL)
	{
		if (info->redirs[i][0] == '>')
			redirect_processing_out(info, i);
		else if (info->redirs[i][0] == '<')
			redirect_processing_in(info, i);
		if (errno != 0)
		{
			ft_putstr_fd(info->redirs[i + 1], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (errno);
		}
		i = i + 2;
	}
	return (0);
}

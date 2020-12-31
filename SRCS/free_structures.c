/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:50:02 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:58:03 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

void		free_general(t_general *general)
{
	free(general->pipe_fd);
	free(general->pipe_fd2);
	free(general);
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

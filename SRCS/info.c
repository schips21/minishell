/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:41:11 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/04 15:29:35 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

t_info		*get_info_echo(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->type = ft_strdup("echo");
	info->n_flag = 1;
	info->args = malloc(sizeof(char **));
	(info->args)[0] = strdup("Hello, world!");
	info->args_num = 1;
	return (info);
}


t_info		*get_info_export(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->type = ft_strdup("export");
	info->args_num = 4;
	info->args = malloc(sizeof(char **)*4);
	(info->args)[0] = ft_strdup("PO=f");
	(info->args)[1] = ft_strdup("F=");
	(info->args)[2] = ft_strdup("8");
	(info->args)[3] = NULL;
	return (info);
}

t_info		*get_info_pwd(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->type = ft_strdup("pwd"); //pwd
	info->n_flag = 0;
	info->args = NULL;
	info->args_num = 0;
	info->redirs = malloc(7 * sizeof(char **));
	(info->redirs)[0] = ft_strdup(">>");
	(info->redirs)[1] = ft_strdup("next");
	(info->redirs)[2] = ft_strdup(">");
	(info->redirs)[3] = ft_strdup("new");
	(info->redirs)[4] = ft_strdup(">>");
	(info->redirs)[5] = ft_strdup("new_file");
	(info->redirs)[2] = NULL;
	info->in = 0;
	info->out = 1;
	return (info);
}

t_info		*get_info_cd(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->type = ft_strdup("cd"); //cd
	info->n_flag = 0;
	info->args = malloc(sizeof(char **));
	(info->args)[0] = strdup("popopo");
	info->redirs = malloc(7 * sizeof(char **));
	(info->redirs)[0] = ft_strdup(">");
	(info->redirs)[1] = ft_strdup("next");
	(info->redirs)[2] = ft_strdup(">");
	(info->redirs)[3] = ft_strdup("new");
	(info->redirs)[4] = ft_strdup(">>");
	(info->redirs)[5] = ft_strdup("new_file");
	(info->redirs)[0] = NULL;
	info->in = 0;
	info->out = 1;
	info->args_num = 1;
	return (info);
}

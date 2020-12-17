/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:42:19 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/04 15:18:12 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_header.h"

t_info		*get_info_export_0(void)
{
	t_info	*info;


	info = malloc(sizeof(t_info));
	info->type = ft_strdup("export");
	info->args_num = 0;
	info->args = malloc(sizeof(char **)*4);
	(info->args)[0] = ft_strdup("Hello=er");
	(info->args)[1] = ft_strdup("world");
	(info->args)[2] = ft_strdup("1=6");
	(info->args)[3] = NULL;
	info->args_num = 0;
	info->redirs = NULL;
	info->in = 0;
	info->out = 1;
	return (info);
}

t_info		*get_info_unset(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->type = ft_strdup("unset");
	info->args_num = 4;
	info->args = malloc(sizeof(char **)*4);
	(info->args)[0] = ft_strdup("USER");
	(info->args)[1] = ft_strdup("PWD");
	(info->args)[2] = ft_strdup("8");
	(info->args)[3] = NULL;
	info->redirs = NULL;
	info->in = 0;
	info->out = 1;
	return (info);
}

t_info		*get_info_env(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->type = ft_strdup("env");
	info->args_num = 0;
	info->redirs = NULL;
	info->in = 0;
	info->out = 1;
	return (info);
}


t_info		*get_info_ls(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->type = ft_strdup("export");
	info->args = malloc(sizeof(char **)*4);
	(info->args)[0] = ft_strdup("export");
	(info->args)[1] = NULL;
	info->args_num = 0;
	info->redirs = NULL;
	info->in = 0;
	info->out = 1;
	return (info);
}

t_info		*get_info_env_out(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	info->args = malloc(sizeof(char **)*4);
	(info->args)[0] = ft_strdup("env");
	(info->args)[1] = NULL;
	info->args_num = 0;
	info->redirs = NULL;
	info->in = 0;
	info->out = 1;
	return (info);
}

//int			main(int argc, char **argv, char *envp[])
//{
//	t_info	*info;
//	t_env	*env;
//	int		fd;
//	int		res;
//	FILE	*file;
//    char	buffer[128];
//
//	env = get_env(envp, env);
//	info = get_info_ls();
//	info->envp = envp;
//	process(env, info);
//	info = get_info_env_out();
//	info->envp = envp;
//	process(env, info);
//	free_env(env);
//	return (0);
//}
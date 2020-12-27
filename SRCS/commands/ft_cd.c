/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:32:11 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/04 14:16:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

char	*find_env(t_env *env, char *type)
{
    int	len;

    while (env != NULL)
    {
        len = ft_bigger_str(env->type, type);
        if(ft_strncmp(env->type, type, len) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

/*при изменении cd, появляется переменная oldpwd
меняется pwd
если pwd или oldpwd во время предыщих команд были удалены, они появятся вновь*/

int		cd_error()
{
    ft_putstr_fd("minishell: cd: ", 1);
    ft_putendl_fd(strerror(errno), 1);
    return (errno);
}

int		ch_pwd(t_env *env)
{
    while (env != NULL)
    {
        if(ft_strncmp(env->type, "PWD", 4) == 0)
        {
            free(env->value);
            env->value = getcwd(NULL, 0);
            if (errno != 0)
                cd_error();
            return (errno);
        }
        env = env->next;
    }
    return (0);
}

int		ft_cd(t_info *info, t_env *env)
{
    int		res;
    char	*old_pwd;
    t_env	*env_old_pwd;

    // надо выделять память под env_old_pwd, чтобы ниже можно было фришить
    if ((env_old_pwd = find_env_env(env, "OLDPWD")) != NULL)
    {
        old_pwd = getcwd(NULL, 0); //malloc
        if (old_pwd == NULL)
            return (cd_error());
        env_old_pwd->class = 1;
        // ошибка маллока тут
        // я попробовала это просто закомментить и не фришить, работает, но скорее всего это будет неверно
        if (env_old_pwd->value != NULL)
        {
            free(env_old_pwd->value);
            env_old_pwd->value = NULL;
        }
        env_old_pwd->value = ft_strdup(old_pwd);
    }
    if (info->args_num == 0)
        res = chdir(find_env(env, "HOME"));
    else
        chdir(info->args[1]);
    if (errno != 0)
    {
        free(old_pwd);
        ft_putstr_fd("minishell: cd: ", 1);
        if (res == -1)
            ft_putendl_fd("HOME not set", 1);
        else
        {
            ft_putstr_fd(info->args[1], 1);
            ft_putstr_fd(": ", 1);
            ft_putendl_fd(strerror(errno), 1);
        }
        return (errno);
    }
    return (ch_pwd(env));
}

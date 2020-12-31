/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_commands_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:41:49 by dskittri          #+#    #+#             */
/*   Updated: 2020/12/31 15:23:51 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell_header.h"

static	size_t	assign_l(size_t len_s1, const char *s1, char *pointer)
{
	size_t		i;

	i = 0;
	while (i != len_s1)
	{
		pointer[i] = s1[i];
		i++;
	}
	return (i);
}

char			*ft_strjoin_path(char const *s1, char const *s2, char a)
{
	size_t		len_s1;
	size_t		len_s2;
	size_t		i;
	char		*pointer;

	if (s1 && s2)
	{
		len_s1 = ft_strlen((char *)s1);
		len_s2 = ft_strlen((char *)s2);
		pointer = (char *)malloc(len_s1 + len_s2 + 2);
		if (pointer == 0)
			return (0);
		assign_l(len_s1, s1, pointer);
		pointer[len_s1] = a;
		i = assign_l(len_s2, s2, &pointer[len_s1 + 1]);
		pointer[i + len_s1 + 1] = '\0';
		return (pointer);
	}
	return (0);
}

void			free_arr(char **array)
{
	int			i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

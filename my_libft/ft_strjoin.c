/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <dskittri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/10/16 05:44:23 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len_s1;
	size_t		len_s2;
	size_t		i;
	char		*pointer;

	if (s1 && s2)
	{
		len_s1 = ft_strlen((char *)s1);
		len_s2 = ft_strlen((char *)s2);
		pointer = (char *)malloc(len_s1 + len_s2 + 1);
		if (pointer == 0)
			return (0);
		assign_l(len_s1, s1, pointer);
		i = assign_l(len_s2, s2, &pointer[len_s1]);
		pointer[i + len_s1] = '\0';
		return (pointer);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <patutinaek@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/04/30 15:03:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	missings(char const *s1, char const *set)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (s1[i] != '\0')
	{
		c = 0;
		while (s1[i] != set[c] && set[c] != '\0')
			c++;
		if (set[c] == '\0')
			break ;
		i++;
	}
	return (i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	unsigned int i;
	unsigned int c;
	unsigned int end;
	unsigned int len_s1;

	end = 0;
	if (s1 == 0 || set == 0)
		return (0);
	i = missings(s1, set);
	if (s1[i] == '\0')
		return (ft_strdup(""));
	len_s1 = ft_strlen((char *)s1) - 1;
	while (len_s1 - end != i)
	{
		c = 0;
		while (s1[len_s1 - end] != set[c] && set[c] != '\0')
			c++;
		if (set[c] == '\0')
			break ;
		end++;
	}
	end = len_s1 - end;
	return (ft_substr(s1, i, (size_t)(end - i + 1)));
}

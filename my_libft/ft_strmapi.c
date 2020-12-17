/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <patutinaek@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/04/30 15:03:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len_s;
	int		i;
	char	*pointer;

	if (f == 0)
		return (0);
	i = 0;
	if (s == 0)
		return (0);
	else
		len_s = ft_strlen((char *)s);
	pointer = (char *)malloc(len_s + 1);
	if (pointer == 0)
		return (0);
	while (i != len_s)
	{
		pointer[i] = f(i, s[i]);
		i++;
	}
	pointer[i] = '\0';
	return (pointer);
}

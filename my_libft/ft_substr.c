/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <patutinaek@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/04/30 15:03:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	counter;
	char			*pointer;

	i = 0;
	counter = 0;
	if (s == 0)
		return (0);
	if (ft_strlen((char *)s) < start)
		return (ft_strdup(""));
	while (s[start + i] != '\0' && i < len)
		i++;
	pointer = (char *)malloc(i + 1);
	if (pointer == 0)
		return (0);
	while (counter != i)
	{
		pointer[counter] = s[start + counter];
		counter++;
	}
	pointer[counter] = '\0';
	return (pointer);
}

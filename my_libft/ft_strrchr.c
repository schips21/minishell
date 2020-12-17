/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <patutinaek@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/04/30 15:03:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char		*ft_strrchr(const char *string, int c)
{
	char	*str;
	int		i;
	char	*result;

	result = 0;
	i = 0;
	str = (char *)string;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == c)
			result = str + i;
		i++;
	}
	if (c == '\0')
		result = str + i;
	return (result);
}

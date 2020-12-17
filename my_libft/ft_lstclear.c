/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dskittri <patutinaek@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 14:40:59 by dskittri          #+#    #+#             */
/*   Updated: 2020/04/30 15:03:19 by dskittri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*successor;

	if (*lst)
	{
		while ((*lst)->next)
		{
			successor = (*lst)->next;
			ft_lstdelone((*lst), del);
			(*lst) = successor;
		}
		ft_lstdelone((*lst), del);
		*lst = NULL;
	}
	return (NULL);
}

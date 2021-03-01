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

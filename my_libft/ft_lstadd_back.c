#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*element;

	if (*lst && new)
	{
		element = ft_lstlast(*lst);
		element->next = new;
	}
	else if (new)
	{
		*lst = new;
	}
}

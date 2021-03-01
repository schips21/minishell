#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *first_elem;
	t_list *result;

	if (lst && f)
	{
		first_elem = ft_lstnew(f(lst->content));
		if (first_elem == 0)
			return (0);
		result = first_elem;
		lst = lst->next;
		while (lst)
		{
			first_elem = ft_lstnew(f(lst->content));
			if (first_elem == 0)
			{
				ft_lstclear(&result, del);
				return (0);
			}
			lst = lst->next;
			ft_lstadd_back(&result, first_elem);
		}
		return (result);
	}
	return (0);
}

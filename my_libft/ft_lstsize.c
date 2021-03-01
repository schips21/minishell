#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int	result;

	result = 0;
	while (lst != 0)
	{
		lst = (lst->next);
		result++;
	}
	return (result);
}

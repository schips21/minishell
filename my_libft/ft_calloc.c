#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*p;

	i = 0;
	p = (void *)malloc(count * size);
	if (p == NULL)
		return (0);
	while (i != count * size)
	{
		((char *)p)[i] = 0;
		i++;
	}
	return (p);
}

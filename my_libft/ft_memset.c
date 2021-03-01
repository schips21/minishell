#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	while (len != 0)
	{
		((unsigned char*)b)[len - 1] = (unsigned char)c;
		len--;
	}
	return ((void *)b);
}

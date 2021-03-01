#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void *dst_original;

	dst_original = dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n != 0)
	{
		n--;
		((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
	}
	return ((void *)dst_original);
}

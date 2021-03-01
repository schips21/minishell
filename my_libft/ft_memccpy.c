#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*srce;

	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest[i] = srce[i];
		if (srce[i] == (unsigned char)c)
			return ((void *)dst + (i + 1));
		i++;
	}
	return (NULL);
}

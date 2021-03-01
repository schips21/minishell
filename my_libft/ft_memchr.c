#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i != n && *((unsigned char *)s + i) != (unsigned char)c &&
	*((unsigned char *)s + i) != '\0')
		i++;
	if (i == n)
		return (0);
	if (*((unsigned char *)s + i) == (unsigned char)c)
		return (void *)(s + i);
	else
		return (0);
}

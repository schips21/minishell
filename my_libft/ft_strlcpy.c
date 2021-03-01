#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t count_src;
	size_t i;

	count_src = 0;
	i = 0;
	if (dst == src)
		return (0);
	while (src[count_src] != '\0')
		count_src++;
	while (src[i] != '\0' && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (count_src);
}

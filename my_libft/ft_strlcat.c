#include "libft.h"

size_t				ft_strlcat(char *dst, const char *src, size_t allsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	i = 0;
	if (allsize < dst_len)
		return (src_len + allsize);
	while (i + dst_len + 1 < allsize && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (i != allsize && dst_len <= allsize)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

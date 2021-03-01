#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*dst;
	size_t	i;
	int		count;

	i = 0;
	dst = (char *)haystack;
	if (needle[0] == '\0')
		return (dst);
	while (i < len && *(dst + i) != '\0')
	{
		count = 0;
		while (*(needle + count) == *(dst + i + count) && (i + count) < len &&
							*(needle + count) != '\0')
			count++;
		if (*(needle + count) == '\0')
			return (dst + i);
		i++;
	}
	return (0);
}

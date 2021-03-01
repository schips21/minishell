#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*p;
	size_t	i;

	len = ft_strlen((char*)s1);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == NULL)
		return (0);
	i = 0;
	while (i != len + 1)
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}

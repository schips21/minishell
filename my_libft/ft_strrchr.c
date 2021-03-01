char		*ft_strrchr(const char *string, int c)
{
	char	*str;
	int		i;
	char	*result;

	result = 0;
	i = 0;
	str = (char *)string;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == c)
			result = str + i;
		i++;
	}
	if (c == '\0')
		result = str + i;
	return (result);
}

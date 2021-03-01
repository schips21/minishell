char		*ft_strchr(const char *str, int c)
{
	int		i;
	char	*string;

	string = (char *)str;
	i = 0;
	while (*(string + i) != c && *(string + i) != '\0')
		i++;
	if (*(string + i) == '\0' && c != '\0')
		return (0);
	else
		return (string + i);
}

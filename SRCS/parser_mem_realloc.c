#include "shell_header.h"

int 	new_word_next(t_info *parsed, int i, int j)
{
	char	**new;

	while (parsed->args[i])
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 2))))
		return (0);
	new[i] = NULL;
	new[i + 1] = NULL;
	while (j < i)
	{
		new[j] = parsed->args[j];
		j++;
	}
	free(parsed->args);
//	parsed->args = NULL;
	parsed->args = new;
	return (j);
}

int 	new_word(t_info *parsed)
{
	if (!parsed->args)
	{
		if (!(parsed->args = malloc(sizeof(char *) * 2)))
			return (0);
		parsed->args[0] = NULL;
		parsed->args[1] = NULL;
		return (0);
	}
	else
		return(new_word_next(parsed, 0, 0));
}

int		new_letter_next(t_info *parsed, int arg_i, char let)
{
	char *new;
	int len;
	int i;

	len = ft_strlen(parsed->args[arg_i]);
	if (!(new = malloc(sizeof(char) * (len + 2))))
		return (0);
	i = 0;
	while (parsed->args[arg_i][i] != '\0')
	{
		new[i] = parsed->args[arg_i][i];
		i++;
	}
	new[i] = let;
	new[i + 1] = '\0';
	free(parsed->args[arg_i]);
	parsed->args[arg_i] = new;
	return (i);
}

int		new_letter(t_info *parsed, int arg_i, char let)
{
	if (!parsed->args[arg_i])
	{
		if (!(parsed->args[arg_i] = malloc(sizeof(char) * 2)))
			return (0);
		parsed->args[arg_i][0] = let;
		parsed->args[arg_i][1] = '\0';
		return (0);
	}
	else
		return(new_letter_next(parsed, arg_i, let));
}

//int		make_type(t_info *parsed, int n_flag)
//{
//	char	**new;
//	int i;
//	int j;
//
//	if (n_flag == 0)
//		parsed->type = parsed->args[0];
//	i = 1;
//	while (parsed->args[i])
//		i++;
//	if (!(new = malloc(sizeof(char *) * (i))))
//		return (0);
//	new[i - 1] = NULL;
//	j = 0;
//	while (j < i - 1)
//	{
//		new[j] = parsed->args[j + 1];
//		j++;
//	}
//	free(parsed->args);
//	parsed->args = NULL;
//	//чтобы не было сигаборта для случая, когда у нас только тип, а аргумента нет
//	if (new[0])
//		parsed->args = new;
//	else
//		free(new);
//	return (0);
//}

int		make_type(t_info *parsed, int n_flag)
{
	char	**new;
	int i;
	int j;

	if (n_flag == 0)
		n_flag = 0;
	i = 1;
	while (parsed->args[i])
		i++;
	if (!(new = malloc(sizeof(char *) * (i))))
		return (0);
	new[i - 1] = NULL;
	new[0] =  parsed->args[0];
	j = 1;
	while (j < i - 1)
	{
		new[j] = parsed->args[j + 1];
		j++;
	}
	free(parsed->args);
	parsed->args = NULL;
	//чтобы не было сигаборта для случая, когда у нас только тип, а аргумента нет
	if (new[0])
		parsed->args = new;
	else
		free(new);
	return (0);
}

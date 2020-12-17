#include "shell_header.h"

int		is_type(char *line, int i)
{
	if (ft_strncmp(line, "echo ", 5) != 0 || ft_strncmp(line, "cd ", 3) != 0
	|| ft_strncmp(line, "pwd ", 4) != 0 || ft_strncmp(line, "export ", 7) != 0
	|| ft_strncmp(line, "unset ", 6) != 0 || ft_strncmp(line, "env ", 4) != 0
	|| ft_strncmp(line, "exit ", 5) != 0)
		return (1);
	return (0);
}

int check_new_arg(char *line, int *i, int end)
{
	//переменная, считающая количество экранирований и кавычек
	int c_scr;
	int start;

	c_scr = 0;
	start = *i;
	while(line[*i] != ' ' && line[*i] != '\0' && line[*i] != '>' && line[*i] != '<' && *i < end)
	{
		if (line[*i] == '\'' && !(line[*i - 1] == '\\' && line[*i - 2] != '\\'))
		{
			(*i)++;
			while (line[*i] != '\'')
				(*i)++;
			(*i)++;
			c_scr += 2;
		}
		else if (line[*i] == '\"' && !(line[*i - 1] == '\\' && line[*i - 2] != '\\'))
		{
			(*i)++;
			while (line[*i] != '\"' && !(line[*i - 1] == '\\' && line[*i - 2] != '\\'))
			{
				if (line[*i] == '\\')
				{
					*i += 2;
					c_scr++;
				}
				else
					(*i)++;
			}
			(*i)++;
			c_scr += 2;
		}
		else
		{
			if (line[*i] == '\\')
			{
				*i += 2;
				c_scr++;
			}
			else
				(*i)++;
		}
	}
	//возвращаем длину слова
	return (*i - c_scr - start);
}

//функция, которая маллочит тип и записывает его в структуру
int		parser_type(char *line, t_info *parsed, int i, int word_len)
{
	int j; //счетчик для массива типа
	int k; //счетчик, который мы добавляем к i когда идем по исходной строке

	if (!(parsed->type = malloc(sizeof(char) * (word_len + 1))))
		return (0);
	j = 0;
	k = 0;
	while (j < word_len)
	{
		if (line[i + k] == '\\')
		{
			k++;
			parsed->type[j++] = line[i + k++];
		}
		else if (line[i + k] == '\'')
		{
			k++;
			while (line[i + k] != '\'')
				parsed->type[j++] = line[i + k++];
		}
		else if (line[i + k] == '\"')
		{
			k++;
			while (line[i + k] != '\"')
			{
				//добавить условие - если нашли доллар, то все, что до пробела, ковычки, конца строки ищем в переменных окр
				//если нашлась переменная - записываем путь, если не нашлось - ничего не записываем
				//соответтсвенно проверить выделение памяти с учетом доллара
				//if (line[i + k] == '$' && !(line[i + k - 1] == '\\' && line[i + k - 2] != '\\'))
				parsed->type[j++] = line[i + k++];
			}
		}
		//добавить else if с долларом
		else
			parsed->type[j++] = line[i + k++];
	}
	parsed->type[j] = '\0';
	return (i + k);
}

int 	parser_one_word(char *line, t_info *parsed, int arg_i, int word_len)
{
	int i; //счетчик для исходной строки
	int j; //счетчик для новой строки

	i = 0;
	j = 0;

	if (!(parsed->args[arg_i] = malloc(sizeof(char) * (word_len + 1))))
		return (0);
	while (j < word_len)
	{
		if (line[i] == '\\')
		{
			i++;
			parsed->args[arg_i][j++] = line[i++];
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
			{
				parsed->args[arg_i][j++] = line[i++];
			}

		}
		else if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"')
			{
				//добавить условие - если нашли доллар, то все, что до пробела, ковычки, конца строки ищем в переменных окр
				//если нашлась переменная - записываем путь, если не нашлось - ничего не записываем
				//соответтсвенно проверить выделение памяти с учетом доллара
				//if (line[i + k] == '$' && !(line[i + k - 1] == '\\' && line[i + k - 2] != '\\'))
				parsed->args[arg_i][j++] = line[i++];
			}
		}
			//добавить else if с долларом
		else
		{
			parsed->args[arg_i][j++] = line[i++];
		}

	}
	parsed->args[arg_i][j] = '\0';
	return (i);
}

//функция, которая считает количество аргументов, чтобы замаллочить двумерный массив
int 	count_args(char *line, t_info *parsed, int i, int type, int end)
{
	int count;
	int quot_1;
	int quot_2;

	count = 0;
	quot_1 = 0;
	quot_2 = 0;
	while (line[i] != '\0' && i < end)
	{
		if (line[i] == ' ' && !(quot_1 == 1 || quot_2 == 1))
		{
			count++;
			while (line[i] == ' ')
				i++;
		}
			//проверка открывающихся и закрывающихся кавычек
			//тут проверить выход за границы массива, когда проверяю i - 1/2
		else
		{
			if (line[i] == '\'' && quot_1 == 0 && !(line[i - 1] == '\\'
			&& line[i - 2] != '\\') && quot_2 == 0)
				quot_1 = 1;
			else if (line[i] == '\'' && quot_1 == 1 && !(line[i - 1] == '\\'
			&& line[i - 2] != '\\') && quot_2 == 0)
				quot_1 = 0;
			else if (line[i] == '\"' && quot_2 == 0 && !(line[i - 1] == '\\'
			&& line[i - 2] != '\\') && quot_1 == 0)
				quot_2 = 1;
			else if (line[i] == '\"' && quot_2 == 1 && !(line[i - 1] == '\\'
			&& line[i - 2] != '\\') && quot_1 == 0)
				quot_2 = 0;
			i++;
		}
	}
	if (line [i - 1] != ' ')
		count++;
	if (!(parsed->args = malloc(sizeof(char *) * (count + 1 - type))))
		return (0);
	//можно вернуть количество аргументов
	return (1);
}

void 	parser_word(char *line, t_info *parsed, int i, int end)
{
	int word_start;
	int arg_i;
	int type;
	int word_len;

	word_start = i;
	arg_i = 0;
	type = is_type(line, i);
	//Выдедяем память под количество аргументов. Если у нас есть команда, нужно выделять на 1 меньше
	while (line[i] == ' ')
		i++;
	count_args(line, parsed, i, type, end);
	while (line[i] != '\0' && i < end)
	{
		word_start = i;
		//найти конец слова, i
		//i - конец слова, word_len - длина слова с учетом того, что убираем экранирование
		word_len = check_new_arg(line, &i, end);
//		while (line[i] != ' ')
//			i++;
		if (arg_i == 0 && type == 1)
		{
			parser_type(line, parsed, word_start, word_len);
			type = 0;
		}
		else
		{
			parser_one_word((line + word_start), parsed, arg_i++, word_len);
			parsed->args_num++;
		}
		while (line[i] == ' ')
			i++;
//		не нужно, т.к. уже увеличиваю i в функции check_new_arg
//		i++;
//		word_start = i + 1;
	}
	parsed->args[arg_i] = '\0';
}

void	quot_screen(char *line, int *i)
{
	if (line[*i] == '\\')
		(*i)++;
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] != '\'')
		{
			if (line[*i] == '\\')
				(*i)++;
			(*i)++;
		}
	}
	else if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] != '\"')
		{
			if (line[*i] == '\\')
				(*i)++;
			(*i)++;
		}
	}
	(*i)++;
}

//функция, которая разбивает строку на подстоки при нахождении специального символа
int	parser(char *line, t_info *parsed)
{
	int line_start;

	line_start = parsed->cur_i;
//	while (line[parsed->cur_i] != '\0')
//	{
//		while (line[i] != ';' && line[i] != '<' && line[i] != '>' && line[i] != '|' && line[i] != '\0')
		while (line[parsed->cur_i] != ';' && line[parsed->cur_i] != '\0')
			quot_screen(line, &parsed->cur_i);
		parser_word(line, parsed, line_start, parsed->cur_i);
		if (line[parsed->cur_i] != '\0')
			parsed->cur_i++;
		parsed->cur_i = parsed->cur_i;
		line_start = parsed->cur_i;
//	}
	return (parsed->cur_i);
}

int main()
{
	t_info parsed;
	int i;
	int j;
	char *line = "echo \"123    abc > cat1\" gkgkgl ; echo 2\\\" \\\"abc\\\"\\'123\\'";

	i = 0;
	while(line[i] != '\0')
	{
		ft_bzero(&parsed, sizeof(parsed));
		parsed.cur_i = i;
		parser(line, &parsed);
		i = parsed.cur_i;
		if (parsed.type != NULL)
			printf("%s", parsed.type);
		j = 0;
		while (j != parsed.args_num)
			printf("\n%s", parsed.args[j++]);
		printf("\n\n");
		//очистка
		free(parsed.type);
		parsed.type = NULL;
		j = 0;

		while (j != parsed.args_num)
			free(parsed.args[j++]);
		free(parsed.args);
		parsed.args = NULL;
//		free(&parsed);
	}
	return (0);
}

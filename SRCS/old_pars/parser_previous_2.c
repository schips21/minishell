#include "shell_header.h"

void 	parser_one_word(char *line, t_info *parsed, int start, int end, int arg_i)
{
	//нужно учитывать, что пробелы могут находиться в кавычках
	int count;
	int i;

	count = 0;
	i = 0;
	while (start + i < end)
	{
		if (!(
		((line[start + i] == '\'' || line[start + i] == '\"') &&
		!(line[start + i - 1] == '\\' && line[start + i - 2] != '\\'))
		|| (line[start + i] == '\\' && line[start + i - 1] == '\\')
		))
			count++;
		i++;
	}
	parsed->args[arg_i] = malloc(sizeof(char) * (count + 1));
	//заполнить массив знаками аргумента
}

void 	parser_word(char *line, t_info *parsed, int i)
{
	int word_start;
	int arg_i;

	word_start = i;
	arg_i = 0;
	while (line[i] != '\0')
	{
		//нужно учитывать, что пробелы могут находиться в кавычках
		while (line[i] != ' ')
			i++;
		parser_one_word(line, parsed, word_start, i, arg_i++);
		i++;
		word_start = i + 1;
	}
}

//функция, которая считает количество аргументов, чтобы замаллочить двумерный массив
void 	count_args(char *line, t_info *parsed, int i)
{
	int count;
	int quot_1;
	int quot_2;

	count = 0;
	quot_1 = 0;
	quot_2 = 0;
	while (line[i] != '\0')
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
	parsed->args = malloc(sizeof(char *) * (count + 1));
}

//функция, которая маллочит тип и записывает его в структуру
int		parser_type(char *line, t_info *parsed, int i)
{
	int count;
	int j;

	count = 0;
	while (line[i + count] != ' ')
		count++;
	if (!(parsed->type = malloc(sizeof(char) * (count + 1))))
		return (0);
	j = 0;
	while (j < count)
	{
		parsed->type[j] = line[i + j];
		j++;
//		count++;
	}
	return (i + j);
}

//функция, которая обрабатывает каждую строку по отдельности
void	parser_line(char *line, t_info *parsed, int start, int end)
{
	while (line[start] == ' ')
		start++;
	start = parser_type(line, parsed, start);
	//или тут будет меньше или равно?
//	while (line[start] != '\0' && start < end)
//	{
//		while (line[start] == ' ')
//			start++;
//		count_args(line, parsed, start);
		//нужно записать все аргументы раздельно в двумерный массив, без кавычек и проверить экранирование
//		parser_word(line, parsed, start);
//	}
}

//функция, которая разбивает строку на подстоки при нахождении специального символа
void	parser(char *line, t_info *parsed)
{
	int i;
	int line_start;
//	int flag;

	i = 0;
	line_start = 0;
//	flag = 0;
	while (line[i] != '\0')
	{
		printf("%c\n", line[i]);
		while (line[i] != ';' && line[i] != '<' && line[i] != '>' && line[i] != '|' && line[i] != '\0')
		{
			if (line[i] == '\\')
				i += 2;
			else if (line[i] == '\'')
			{
				i++;
				while (line[i] != '\'')
				{
					if (line[i] == '\\')
						i += 2;
					else
						i++;
				}
				i++;
			}
			else if (line[i] == '\"')
			{
				i++;
				while (line[i] != '\"')
				{
					if (line[i] == '\\')
						i += 2;
					else
						i++;
				}
				i++;
			}
			else
				i++;
		}

		parser_line(line, parsed, line_start, i);
		i++;
		line_start = i;


//		нужно ли здесь добавлять кейс >>? Или его можно проверить дальше при нахождени >?
//		if (((line[i] == ';' || line[i] == '<' || line[i] == '>' || line[i] == '|')
//		&& (!(line[i - 1] == '\\' && line[i - 2] != '\\')))
//		|| line[i + 1] == '\0'
//		)
//		{
//			вызов функции, в которую мы передаем первый и последний элемент части строки
//			parser_line(line, parsed, line_start, i);
//			line_start = i;
//			flag = 1;
//		}
//		i++;
	}
//	if (flag == 0)
//		parser_line(line, parsed, 0, i);
}

int main()
{
	t_info parsed;
	char *line = "echo   \"123    abc > cat t1\"";

	ft_bzero(&parsed, sizeof(parsed));
	parser(line, &parsed);
//	printf("%s\n%s\n%s\n", parsed.type, parsed.args[0], parsed.args[1]);
	printf("%s\n", parsed.type);
	return (0);
}
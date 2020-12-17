#include "shell_header.h"

//функция, которая используется для нахождения длины аргумента кроме редиректов
int check_new_arg(char *line, t_info *parsed, int *i, int end)
{
	//переменная, считающая количество экранирований и кавычек
	int c_scr;
	int start;
	int redir_count;

	c_scr = 0;
	start = *i;
	redir_count = 0;
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
//		else if (line[*i] == '>' || line[*i] == '<')
//		{
//			*i++;
//			if (line[*i] == '>' && line[*i - 2] == '>')
//				*i++;
//			while(line[*i] == ' ')
//				*i++;
//			while(line[*i] != ' ')
//				*i++;
//			redir_count += 2;
//		}
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
	parsed->redir_utils->redir_num = redir_count;
	if (!(parsed->redir = malloc(sizeof(char *) * (redir_count + 1))))
		return (0);
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

//	т.к. первый аргумент мы отправили в type
	arg_i--;
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
int 	count_args(char *line, t_info *parsed, int i, int end)
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
	//не делаем +1, т.к. первый аргумент мы отправляем в type
	//вычитаем количество редиректов, т.к. они здесь тоже посчитаются как аргументы
	if (!(parsed->args = malloc(sizeof(char *) * (count - parsed->redir_utils->redir_num))))
		return (0);
	//можно вернуть количество аргументов
	return (1);
}

void 	parser_word(char *line, t_info *parsed, int i, int end)
{
	int word_start;
	int arg_i;
	int word_len;

	arg_i = 0;
	while (line[i] == ' ')
		i++;
	//Выдедяем память под количество аргументов. Т.к. у нас всегда есть команда, нужно выделять на 1 меньше
	count_args(line, parsed, i, end);
	while (line[i] != '\0' && i < end)
	{
		word_start = i;

		//check_new_arg вызываю только для аргументов без редиректов
		// т.к. эта функция может неправильно распознать редиректы
		if (line[i] == '>' || line[i] == '<')
		{
			parser_redir(line, parsed, &i, end);
		}
		else if (arg_i == 0)
		{
			//i - конец слова, word_len - длина слова с учетом того, что убираем экранирование
			word_len = check_new_arg(line, parsed, &i, end);
			parser_type(line, parsed, word_start, word_len);
			arg_i++;
		}
		else
		{
			//i - конец слова, word_len - длина слова с учетом того, что убираем экранирование
			word_len = check_new_arg(line, parsed, &i, end);
			parser_one_word((line + word_start), parsed, arg_i++, word_len);
			parsed->args_num++;
		}
		while (line[i] == ' ')
			i++;
	}
	// или здесь нужно замалочить 1 эелемент и '\0' подставить в нулевой элемент?
	parsed->args[arg_i - 1] = '\0';
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
	while (line[parsed->cur_i] != ';' && line[parsed->cur_i] != '\0')
		quot_screen(line, &parsed->cur_i);
	parser_word(line, parsed, line_start, parsed->cur_i);
	if (line[parsed->cur_i] != '\0')
		parsed->cur_i++;
//	parsed->cur_i = parsed->cur_i;
//	line_start = parsed->cur_i;
	return (parsed->cur_i);
}

int main()
{
	t_info parsed;
	int i;
	int j;
	char *line = "echo \"hello><\"; world";

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

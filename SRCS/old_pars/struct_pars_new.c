typedef struct s_info2
{
	char *line;
	char **args;
	int i;
	char *tmp;
	char *tmp2;
}               t_info2;

void quotes_one
{
	while(!'\'')
	{
		tmp2 = line[i];
	}
};

int parsing(info)
{
	while(i != '\0')
	{
		if(line[i] == '\'')
			quotes_one(info);
		else if(line[i] == '\"')
			quotes_two(info);
		else
			qoutes_no(info);
		if(;|)
			return(1);
	}
	return (0);
}

void get_args(char *line)
{
	int arg_status;

	arg_status = 1;
	while(arg_status)
	{
		arg_status = parsing(info2);
		execute(info2);
		free(args);
	}
}

int main()
{


	get_args(line);
	gnl(line);

}
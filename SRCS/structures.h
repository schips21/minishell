typedef struct			s_info
{
	char				*type;
	int					n_flag;
	char				**args;
	int					args_num;
	void				*next;
	int					in;
	int					out;

	char				**redirs;
	int					cur_i;
	int					pipe;

	char				**envp;
}						t_info;

typedef struct		s_red_utils
{
	int				redir_num;
	int 			cur_i;
}					t_red_utils;

typedef struct		s_env
{
	char			*type;
	char			*value;
	int				class;
	struct s_env	*next;	
}					t_env;
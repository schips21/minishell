#include <string.h>
#include "structures.h"
# include "../my_libft/libft.h"
#include<unistd.h>
#include<errno.h>
#include <dirent.h>
#include <fcntl.h>

extern int WRITE_END;
extern int READ_END;
int g_res;

//mem_realloc.c
int 	new_word_next(t_info *parsed, int i, int j);
int 	new_word(t_info *parsed);
int		new_letter_next(t_info *parsed, int arg_i, char let);
int		new_letter(t_info *parsed, int arg_i, char let);
int		make_type(t_info *parsed, int n_flag);

//mem_realloc_redir.c
int 	new_word_next_red(t_info *parsed, int i, int j);
int 	new_word_red(t_info *parsed);
int		new_letter_next_red(t_info *parsed, int red_i, char let);
int		new_letter_red(t_info *parsed, int red_i, char let);


//parser_utils.c
void	two_quot(char *line, t_info *parsed, int *i, t_env *env);
void	parse_echo_n(t_info *parsed);
void	count_args(t_info *parsed);

//parser_redirects.c
void	two_quot_red(char *line, t_info *parsed, int red_i, int *i);
void	parser_redir(char *line, t_info *parsed, int *i);

//parser_dollar.c
char	*pars_dollar_create_env(char *line, int *i, int count);
char	*pars_dollar(char *line, int *i);
void	pars_dollar_env(t_info *parsed, t_env *env, int arg_i, char *env_str);

/* Shell functions */
void	ft_echo(t_info *info);
int		ft_pwd(t_info *info);
int		ft_cd(t_info *info, t_env *env);
int		ft_export(t_info *info, t_env *env, int fd);
int		ft_unset(t_info *info, t_env *env);
void	ft_env(t_env *env, int fd);
void	ft_exit(t_info *info);

/* Ready structures for commands */
t_info	*get_info_echo(void);
t_info	*get_info_pwd(void);
t_info	*get_info_cd(void);
t_info	*get_info_export(void);


/*Main process */
int		process(t_env *env, t_info *info, t_general *general);
/* Redirects */
int			redirect_processing(t_info *info);

/* Functions for env structure */
t_env	*ft_envlast(t_env *env);
t_env	*ft_envnew(void *type, void *value, int class);
void	ft_lstenv_back(t_env **env, t_env *new);
t_env	*get_env(char **envp, t_env *first);
t_env	*get_env_type_value(char **envp, int count);
void	*free_env(t_env *env);
char	*find_env(t_env *env, char *type);

/* To change pwd after cd */
int		ch_pwd(t_env *env);

void	print_my_env(t_env *env);

/* Export functions */
void	ft_change_elem(t_env **previous, t_env **first, t_env **second, t_env **start);
t_env	*sort_env(t_env *start);
t_env	*copy_env(t_env *env);
void	print_export(t_env *env, int fd);
void	simple_export(t_env *env, int fd);

int			ft_other_commands(t_info *info, t_env *env, t_general *general);
char			*ft_strjoin_path(char const *s1, char const *s2);


char	*ft_def_strdup(char *s1);

void		*free_other(char *type, char *value);
t_env		*find_env_env(t_env *env, char *type);
int ft_bigger_str(char *str1, char *str2);

int			pipe_write_only(t_info *info, t_env *env, t_general *general);
int			pipe_read_only(t_info *info, t_env *env, t_general *general);
void		read_from_pipe(int *fd, t_info *info, t_env *env);
int		command_execution(t_info *info, t_env *env, t_general *general);

//parser.c
int		parser(char *line, t_info *parsed, t_env *env);

//parser_check_line.c
int		parser_check_line(char *line, t_info *info);
void	parser_check_line_skip(char *line, int *i, t_line_check *line_check);
void	parser_check_line_skip_quot(char *line, int *i, t_line_check *line_check);
int		parser_check_line_ret(t_info *info);
void	parser_check_line_util(char *line, t_line_check *line_check, int *i);
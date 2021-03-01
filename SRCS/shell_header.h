#ifndef SHELL_HEADER_H
# define SHELL_HEADER_H

# include <string.h>
# include "structures.h"
# include "../my_libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include "signal.h"
# include <sys/types.h>
# include <sys/wait.h>

int			g_res;
int			g_ctrl_d;
char		*g_line;

int			parser(char *line, t_info *parsed, t_env *env);
int			parser_return(char *line, t_info *parsed, int i);
void		parser_dollar_start(char *line, t_info *parsed, t_env *env, int *i);
void		parser_spec(char *line, t_info *parsed, t_env *env, int *i);

int			parser_check_line(char *line, int i);
int			parser_check_line_skip(char *line, int *i,
				t_line_check *line_check);
int			parser_check_line_skip_quot(char *line, int *i,
				t_line_check *l_check);
int			parser_check_line_skip_q_one(char *line, int *i,
				t_line_check *l_check);
int			parser_check_line_ret(void);
int			parser_check_line_util(char *line, t_line_check *line_check,
				int *i);
int			parser_check_l_red(char *l, int *i,
				t_line_check *l_check);

int			new_word_next(t_info *parsed, int i, int j);
int			new_word(t_info *parsed);
int			new_letter_next(t_info *parsed, int arg_i, char let);
int			new_letter(t_info *parsed, int arg_i, char let);
int			make_type(t_info *parsed);

int			new_word_next_red(t_info *parsed, int i, int j);
int			new_word_red(t_info *parsed);
int			new_letter_next_red(t_info *parsed, int red_i, char let);
int			new_letter_red(t_info *parsed, int red_i, char let);

void		two_quot(char *line, t_info *parsed, int *i, t_env *env);
void		parse_echo_n(t_info *parsed);
void		count_args(t_info *parsed);

void		two_quot_red(char *line, t_info *parsed, int red_i, int *i);
void		parser_redir(char *line, t_info *parsed, int *i);
void		parser_redir_symb(char *line, t_info *parsed, int *i, int red_i);

char		*pars_dollar_create_env(char *line, int *i, int count);
char		*pars_dollar(char *line, int *i);
void		pars_dollar_env(t_info *parsed, t_env *env, int arg_i,
			char *env_str);

void		ft_echo(t_info *info);
int			ft_pwd(void);
int			ft_cd(t_info *info, t_env *env);
int			ft_export(t_info *info, t_env *env, int fd);
int			ft_unset(t_info *info, t_env *env);
void		ft_env(t_env *env, int fd);
void		ft_exit(t_info *info, t_general *general);

int			process(t_env *env, t_info *info, t_general *general);
int			redirect_processing(t_info *info);

t_env		*ft_envlast(t_env *env);
t_env		*ft_envnew(void *type, void *value, int class);
void		ft_lstenv_back(t_env **env, t_env *new);
t_env		*get_env(char **envp, t_env *first);
t_env		*get_env_type_value(char **envp, int count);
void		*free_env(t_env *env);
char		*find_env(t_env *env, char *type);
t_env		*find_env_env(t_env *env, char *type);

int			ch_pwd(t_env *env);
void		ft_chng_elem(t_env **previous, t_env **first, t_env **second,
			t_env **start);
t_env		*sort_env(t_env *start);
t_env		*copy_env(t_env *env);
void		print_export(t_env *env, int fd);
void		simple_export(t_env *env, int fd);

int			ft_other_commands(t_info *info, t_env *env, t_general *general);
char		*ft_strjoin_path(char const *s1, char const *s2, char a);
char		*ft_def_strdup(char *s1);

void		*free_other(char *type, char *value);
int			ft_bigger_str(char *str1, char *str2);

int			command_execution(t_info *info, t_env *env, t_general *general);
void		last_after_odd_pipe(t_general *general);
void		last_after_even_pipe(t_general *general);
void		middle_after_odd_pipe(t_general *general);
void		middle_after_even_pipe(t_general *general);
void		pipe_execution(t_general *general, t_info *info);
void		pipe_execution_child(t_general *general, t_info *info);
int			execution_child(t_info *info, t_env *env, t_general *general);
int			parents_cmnd_exec(t_info *info, t_env *env, t_general *general);
int			if_parent_process(t_info *info, t_general *general);

int			error_errno(t_info *info);
char		**from_env_to_array(t_env *env);
int			if_file_here(t_info *info, DIR *new);
void		free_arr(char **array);
int			other_error(t_info *info);

void		main_init_gnl(int *i, t_info *parsed, t_general *general);
void		main_free_args_redirs(t_info *parsed, int j);

void		listener(int signal);
int			signals_in_parent(int stat, t_general *general);

int			export_error(char *err, int fd, int i);
void		free_general(t_general *general);
void		main_free_args_redirs(t_info *parsed, int j);
void		parser_tmp(t_info *parsed);
void		dup_after_redir(t_info *info, int dup_in, int dup_out,
			t_general *gen);
char		*check_free_line(char *line, int in, int out);
t_general	*fullfill_general(void);
char		*ft_def_strdup(char *s1);
int			if_other_command(t_info *info);
int			excex_command_new(char *command, t_info *info, t_env *env);
int			ft_other_commands_2_new(t_info *info, t_env *env, char **path_arr);
void		pre_gnl(void);

void		main_pars(t_env *env, t_info *parsed, int *i);
void		main_bef_proc(t_general *gen, int in, int out);
void		main_utils(t_info *parsed);
void		minishell_signal(t_info *parsed);
void		minishell_to_null(t_info *parsed);

#endif

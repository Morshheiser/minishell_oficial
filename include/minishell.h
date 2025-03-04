#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_SIZE 1024
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define USED_CTRL_C 130

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>

typedef struct s_token		t_token;
typedef struct s_pid		t_pid;
typedef struct s_env_node	t_env_node;
typedef struct s_env		t_env;
typedef struct s_cmd		t_cmd;
typedef struct s_shell		t_shell;
typedef struct s_fd			t_fd;

extern int					status_g;

enum						e_fd
{
	IN = 0,
	OUT = 1
};

typedef struct s_pid
{
	int						pid;
	struct s_pid			*next;
}							t_pid;

typedef struct s_fd
{
	char					*fnm;
	int						ffd;
}							t_fd;

typedef struct s_cmd
{
	t_fd					fdin;
	t_fd					fdout;
	char					**args;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_env
{
	char					**var_list;
	char					*pwd;
}							t_env;

typedef struct s_shell
{
	char					**argv;
	t_cmd					*cmd;
	t_pid					*pd;
	int						fd[2];
	t_env					*env;
}							t_shell;

// Function Declarations

void						ft_execute_builtins(char **args, t_env *env,
								t_shell *shell);
void						ft_builtin_exec(t_shell *shell, t_cmd *cmd);
int							ft_is_builtin(char *cmd);

void						ft_update_env(char *path, t_env *env);
void						ft_follow_path(char *path, t_env *env);
void						ft_cd(char **args, t_env *env);

int							ft_echo(char **args);

int							ft_env(t_env *env);

void						ft_end(t_env *env, t_shell *sh);
int							ft_compare_with_limit(char *arg, int i, int len,
								int sign);
int							ft_is_overflow(char *arg);
int							ft_is_all_digit(char *str);
void						ft_exit(char **args, t_env *env, t_shell *shell);

void						ft_free_split(char **split);
int							ft_check_arg(const char *arg);
void						ft_list_env(t_env *env);
// int ft_update_env_var(t_env *env, char **split);
int							ft_update_or_add_var(t_env *env, char *arg);
int							ft_export(char **args, t_env *env);

void						ft_pwd(char **args, t_env *env);

int							ft_search_equal(t_env *env, char *str);
int							ft_validate_identifier(char *identifier);
void						ft_remove_environment_variable(t_env *env,
								int index);
void						ft_unset(char **args, t_env *env);

char						**ft_arr_copy(char **arr, int size);
int							ft_size(char **arr);
int							ft_srch_arr(char **array, char *str);
long long int				ft_atolli(const char *str);

char						*ft_find_env(char *key, char **env);
char						*ft_find_env_value(char *key, char **env);
void						ft_free_arr(char **arr);
void						ft_initialize_env(t_env **env, char **envp);

int							ft_vetor_size(char **ev);
void						ft_env_addback(t_env *env, char *key, char *value);
void						ft_free_env(t_env *env);

void						ft_executor(t_shell *shell);

void						begin_exec(int *pipe_in, t_cmd *cmd, t_shell *shell,
								t_pid **lst_pid);
void						end_exec(int pipe_out, t_cmd *cmd, t_shell *shell,
								t_pid **lst_pid);
void						process_command_pipeline(int orig_pipe,
								t_shell *shell, t_cmd *cmd);
int							confirm(t_cmd *cmd);
void						ft_setfd(int fd, t_fd *files, int s);
void						ft_specific(int fd[2], int *prev_pipe_read,
								t_cmd *cmd, t_shell *shell);
void						ft_wait_pid(t_pid **pid);
void						ft_reset_signal(void);
char						*ft_get_path_name(char *cmd, t_env *env_list);
char						*ft_find_relative(char *cmd, char *env);
void						ft_execve_exec(t_shell *shell, t_cmd *cmd);
char						*ft_handle_absolute_path(char *cmd);

char						*ft_expand_variables(char *input, char **args,
								char **env);

char						*ft_find_exit_status(char **line, int i);
char						*ft_get_env_in_brackets(char **line, char **envp);
char						*ft_get_arg_value(char **line, char **argv);
char						*ft_get_env_variable(char **line, char **env);

char						*ft_expand_env_variable(char **input, char **args,
								char **env);

int							ft_check_double_quote_syntax(char *str);

char						*ft_expand_double_quotes(char **line, char **argv,
								char **env);

char						*ft_expand_single_quotes(char **line);
char						*ft_expand_plain_text(char **line, char *eofs);

// char *ft_strjoin_free(char *s1, char *s2);
char						*ft_merge_strings(char *s1, char *s2);
int							ft_isolate(char **src, char **var);

int							ft_check_lexer(char *line);

int							ft_check_closed_op(char *str);
int							ft_check_pipe_syntax(char *str);
int							ft_check_redir_syntax(char *str, char opt);
int							ft_lex_error(char c, int n);
int							ft_str_is_space(const char *str);
int							ft_isspace(char c);

int							main(int ac, char **av, char **ev);

char						*ft_set_prompt(char **env);
void						go_minibash(char *line, t_shell *shell);
void						run_minibash_loop(t_shell *shell);

void						ft_print_message(char *shell, char *text,
								char *msg);
int							ft_perror(int ret, char *text, char *msg, ...);

void						ft_cleanup_env(t_env *env);
void						ft_cleanup_pid(t_pid *pd);
void						ft_cleanup_fd(int *fd);
void						ft_cleanup_shell_resources(t_shell *shell);
void						ft_cleanup_resources(t_shell *shell, t_pid *pd,
								int *fd, t_env *env);
// int ft_line_is_being_processed(t_shell *shell);

t_shell						start_function(char **argv, char **env);
void						ft_setup_signal_handlers(void);
static void					ft_error_handler_sigint(int sig);
void						parse_input(char *line, t_shell *shell);
// char	*ft_strndup(const char *s1, size_t n);
// char	*ft_strncpy(char *dst, const char *src, size_t len);

void						parse_input(char *line, t_shell *shell);

static char					*ft_set_filename(char *input, t_shell *shell);
static int					ft_input_redirection(char *filename, t_fd *fd_info,
								int operator, t_shell * shell);
static int					ft_output_redirection(char *filename, t_fd *fd_info,
								int operator, t_shell * shell);
int							ft_configure_redirections(char *input,
								t_fd *fd_info, t_shell *shell);
t_cmd						*ft_init_and_process_command(char *input,
								t_shell *shell);
t_cmd						*ft_create_command_from_input(char *input,
								t_shell *shell);
int							ft_find_quote_end(char *str);
void						ft_update_var(char *key, char *value, t_env *env,
								char **update_pwd);

static int					ft_return_heredoc(int fd[2]);
static int					ft_read_heredoc(int fd, char *end_of_file);
int							ft_heredoc(char *end_of_line);
t_cmd						*ft_command_error(t_fd *in, t_fd *out,
								char **split);
static int					ft_process_argument(char **args, int index,
								t_shell *shell);
char						**ft_extract_command_arguments(char *line,
								t_shell *shell);
void						ft_handle_redirection(char *str);
void						ft_clean_redirection_tokens(char *str);
t_cmd						*ft_create_new_command(t_fd *in, t_fd *out,
								char **args);
int							ft_size_arr(char **arr);

void						*ft_check_alloc(void *str, char *text);
char						**ft_arr_copy(char **arr, int size);
void						ft_clean_cmd(t_cmd **cmd);
void						ft_cmd_append(t_cmd **cmd_list, t_cmd *new_cmd);
void						ft_clean_fd(t_fd *fd);
t_pid						*ft_new_pid(int pid);
void						ft_add_back_pid(t_pid **pid, t_pid *node);
void						ft_clean_pid(t_pid **pid);
void						ft_clean_sh(t_shell *shell);
char						**ft_clean_split(char **split);
char						*ft_expand_plain_dollar(char **line, char *eofs);
int							count_escaped_dollar(const char *str);
// int	ft_strcmp(const char *s1, const char *s2);
// char *ft_process_double_quotes(char **input, char **argv, char **env);
char						**ft_free_splterr(char **split);
char						*ft_expand_plain_text(char **line, char *eofs);
char						*ft_expand_plain_eof(char **line, char *eofs);
void						ft_clean_int_fd(int *fd);
char						*ft_get_env(char *key, char **env);

int							ft_count_pipe(char *str);
char						**ft_allocate_split(char *line, const char *set);
char						**ft_split_with_set(char *line, const char *set);
void						change_flag(char c, int *single_flag,
								int *double_flag);

int							ft_count_word(char *line, const char *set);
int							ft_len_word(char *line, const char *set);
char						*ft_sub_word(char *line, int len);

#endif

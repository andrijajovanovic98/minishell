/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:20:26 by bszilas           #+#    #+#             */
/*   Updated: 2024/08/20 17:43:38 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"

# define END 01
# define IN_R 02
# define HEREDOC 04
# define CMD 010
# define PIPE 020
# define INTERPRET 040
# define AMBI_R 0100
# define NO_VAR 0200
# define NO_EXPAND 0400
# define TO_SPLIT CHAR_MAX
# define REDIRECTION 03006
# define READ_END 0
# define WRITE_END 1
# define PIPE_ERROR 129
# define FORK_ERROR 254
# define PROMPT "\001\033[1;31m\002min\001\033[1;37m\002ish\001\033\
[1;32m\002ell\001\033[0m\002 > "
# define HD_PROMPT "\001\033[1;31m\002her\001\033[1;37m\002edo\001\033\
[1;32m\002c \001\033[0m\002\""
# define TMP_PATH "/tmp/.tmp"
# define ENV_PATH "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/\
bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"
# define FILENAME 1
# ifndef TESTER
#  define TESTER 0
# endif

typedef struct s_token
{
	int				type;
	struct s_token	*right;
	struct s_token	*left;
	char			*str;
}				t_token;

typedef struct s_node
{
	int				type;
	struct s_node	*next;
	struct s_node	*prev;
	char			**content;
}					t_node;

typedef struct s_var
{
	struct sigaction	sa;
	t_token				*tokens;
	t_token				*last_token;
	t_node				*list;
	t_node				*current;
	char				*line;
	char				**env;
	char				**stack_env;
	char				**splitted_path;
	char				**compound_arg;
	char				*cwd;
	char				*exec_cmd;
	char				*hd_history;
	char				*prompt;
	char				stack_prompt[4];
	pid_t				pid;
	size_t				len;
	int					pfd[2];
	int					in_fd;
	int					out_fd;
	int					cmds;
	int					status;
	int					last_status;
	int					loop;
	int					overflow;
}						t_var;

/* LEXER */

t_token		*create_token(int type, char *str);
t_token		*tokenize(t_var *var);
int			add_token(t_var *var, char **start);
void		free_tokens(t_var *var);
void		skip_whitespace(char **input);
int			identify_token_type(t_var *var, char **start, char **end);
int			identify_input_redirection(char **start, char **end);
int			identify_output_redirection(char **start, char **end);
int			identify_pipe(char **start, char **end);
int			identify_general_token(t_var *var, char **start, char **end);
int			identify_single_quotes(char **start, char **end);
int			identify_double_quotes(char **start, char **end);
int			lone_dollar_sign(char *start, char *end);
void		ft_strncpy(char	*dest, const char *str, size_t n);
char		*ft_strndup(const char *s, size_t n);
void		add_token_to_list(t_var *var, t_token *new_token);
void		init_token(t_token *new, char *str, int type);
void		mark_whitespaces(char *str);
char		*token_end(char *start);
void		reset_end(char *start, char **end, char *ptr, char *tkn_end);
int			identify_nonexistent_var(t_var *var, char **start, char **end);

/* INTERPRET */

void		cat_char_to_str(char *str, char c, size_t len);
void		cat_single_qoutes(char *str, char **start, char *end, size_t len);
void		cat_env_var(t_var *var, char *str, char **start, char *end);
void		cat_double_qoutes(t_var *var, char *str, char **start, char *end);
char		*cat_intrd_str(t_var *var, char *start, char *end);
size_t		single_quote_len(char *s, char *end, size_t *i);
size_t		env_var_len(t_var *var, char *s, char *end, size_t *i);
size_t		double_qoute_len(t_var *var, char *s, char *end, size_t *i);
size_t		interpreted_str_len(t_var *var, char *start, char *end);
char		*ft_getenv(char **env, char *s);
void		cat_status(char *str, int status, size_t len);
bool		possible_var(t_var *var, char c, char d);
bool		ambiguous_redirect(t_var *var, int type, char *str);
void		free_bare_tokens(t_token *last);
int			split_compound_tokens(t_var *var, char *str);
bool		handle_compound_tokens(t_var *var, char *str);
void		heredoc_expand_line_len(t_var *var, char *line);
char		*expand_heredoc_line(t_var *var, char *line);

/* SIGNAL */

void		setup_signal_handlers(t_var *var);
void		handle_sigint(int sig);
void		sigint_handler_interactive_mode(t_var *var);
void		check_received_signal(t_var *var);
void		save_sigint(int signal);
void		sigint_handler_non_interactive_mode(t_var *var);

/* PARSER */

char		*trim_nl_free(char *line);
t_node		*last_node(t_token *current, t_node *this);
int			token_arg_count(t_token *current);
t_node		*new_command_node(t_token *current, t_node *this);
t_node		*new_pipe_node(t_token *current, t_node *this);
void		set_redirect_type(t_node *this);
t_node		*new_redirect_node(t_token *current, t_node *this);
t_node		*new_list_node(t_token *current);
void		add_to_list(t_var *var, t_node *this);
bool		parse_tokens(t_var *var);
void		unexpected_token(char *str);
bool		double_pipe(t_token *token);
bool		missing_filename(t_token *token);
bool		pipe_in_front(t_token *token);
bool		valid_syntax(t_token *token);
t_token		*find_next_arg_token(t_token *next);
t_token		*find_token(t_token *token, int type, int before_type);
bool		close_pipeline(t_var *var, t_token *start);
bool		make_pipeline(t_var *var, t_token *start);
t_token		*last_token(t_token *start);

/* ERROR_HANDLING */

void		init_var(t_var *var, int argc, char **argv, char **envp);
void		free_linked_lists(t_var *var);
void		free_all(t_var *var);
void		restore_environment(t_var *var);
void		free_lists_and_path(t_var *var);
void		status_1(t_var *var);
void		status(t_var *var, int status);
void		error_exec_txt_file(t_var *var);
void		command_not_found(t_var *var);
void		ambiguous_redirect_error(t_var *var, char *str);
void		invalid_identifier(t_var *var, char *str);
void		error_msg(t_var *var, char *str, int status);
void		child_execve_error_handler(t_var *var);

/* BUILTINS */

void		malloc_envps_or_exit(t_var *var, char **envp);
void		initialize_environment(t_var *var);
char		**command_unset(t_var *var, char *str);
char		**command_export(t_var *var, char *str);
int			valid_identifier(t_var *var, char *str);
void		command_echo(t_var *var);
size_t		envp_string_count(char **envp);
void		command_exit(t_var *var);
void		command_cd(t_var *var, char *path);
bool		too_many_arguments(t_var *var, t_node *cmd);
void		command_pwd(t_var *var);
void		command_env(t_var *var);
int			unset2(char **old_envp, char *dest, size_t to_compare, \
char **new_env);
int			existing_env_var(char **env, char *str);
char		**change_var(char **env, char *str);
void		update_env_after_cd(t_var *var, char *env_var_name, char *path);
void		cd_home(t_var *var, char *path);
int			valid_dotdot_path(char *path);
void		cd_dotdot_for_istvan(t_var *var, char *path);
char		*find_next_smallest(char **arr, char *current, char *max);
void		print_environment(t_var *var);
char		**set_shlvl(t_var *var, char *str);
int			get_shlvl(t_var *var, char *str);
char		**env_loop(t_var *var, char **(*f)(t_var *, char *));
void		update_last_cmd(t_var *var);
char		*last_arg(char **args);
void		update_last_cmd(t_var *var);
void		print_env_string(t_var *var, char *str, int fd);
int			open_fd_export(t_var *var);
long long	signed_llong_overflow_check(t_var *var, char *n);
size_t		to_export_len(char *str);
void		ft_getenv_get_envvar_name(char *s, char **var, char *tmp, \
size_t len);
void		write_or_exit(t_var *var, int fd, const void *buf, size_t n);
void		print_env_location(t_var *var);

/* EXECUTE */

void		execute(t_var *var);
int			cd_export_exit_or_unset(t_var *var);
void		one_simple_cmd(t_var *var);
void		exec_other_commands(t_var *var);
int			count_node_types(t_node *node, int type);
t_node		*get_next_node(t_node *node, int get_type, int before_type);
void		close_in_and_out(t_var *var);
void		exec_system_commands(t_var *var);
char		**splitted_path(t_var *var);
char		*ft_strjoin_three(char *s1, char *s2, char c);
void		close_pipe(int pfd[]);
void		exec_cleanup(t_var *var);
char		*get_cmd(t_var *var);
void		first_cmd(t_var *var);
void		middle_cmd(t_var *var);
void		last_cmd(t_var *var);
void		wait_children(t_var *var);
char		*check_given_file(t_var *var);
void		set_status(t_var *var);
int			search_path(t_var *var, int access_type);
void		get_child_exit_status(t_var *var);

/* REDIRECT */

int			create_tmp_file(t_node *node);
int			open_files_in_parent(t_var *var);
void		redirect_or_exit(t_var *var);
void		redirect_infile(t_var *var, char *file);
void		redirect_outfile(t_var *var, char *file, int type);
int			write_here_docs(t_var *var);
void		heredoc_expand_line_len(t_var *var, char *line);
char		*expand_heredoc_line(t_var *var, char *line);
char		*heredoc_prompt(t_var *var, char *limiter);
void		free_heredoc_prompt(t_var *var);
void		write_doc(t_var *var, char *limiter, int fd, int expand);
void		flag_heredoc(t_var *var);
void		heredoc_warning(int signal, char *limiter);
bool		heredoc_line_possible_var(t_var *var, char *line);

#endif
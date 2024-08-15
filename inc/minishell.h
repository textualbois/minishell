/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:13 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/15 02:56:14 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>

// own lib's
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include "structures.h"

// pipex stuff
# ifndef READ_END
#  define READ_END 0
# endif
# ifndef WRITE_END
#  define WRITE_END 1
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# ifndef CHILD
#  define CHILD 0
# endif
# ifndef ANY_CHILD
#  define ANY_CHILD -1
# endif

// Colors
# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"
# define RESET "\033[m"

// **********************====FUNCTION DECLARATION====*********************
// -------------------------------------------DIR---builtins
// ---cmds.c
int			builtin_echo(char **args);
int			builtin_pwd(void);
int			builtin_exit(t_shell *shell, t_command *cmd);
int			ft_isnum(const char *str);

//change_dir.c
int			builtin_cd(t_shell *shell, char **args);

// ---env.c
int			builtin_env(t_shell *shell, char **args);
int			builtin_unset(t_shell *shell, char *key);
char		*get_env_value(t_env *env_list, char *key);
void		free_env_node(t_env *env_node);

// ---export.c
int			builtin_export(t_shell *shell, char **args);
int			print_env_list(t_env *env_list);
void		update_env_node(t_env *env_list, char *key, char *value);

// -------------------------------------------DIR---exec
// -------------------------------------------DIR---sub_DIR----pipex_api
// ---heredoc.c
int			here_doc4shell(int fd_array[][2], t_command *cmd, char *delimiter);

// ---manage_fd.c
int			set_fds_pipe4shell(int fd_array[][2], int cmd_num, t_command *cmd);
void		close_fds_parent4shell(int fd_array[][2],
				int cmd_num, t_command *cmd);

// ---manage_fd_helpers.c
int			setup_infile_read_fd(int fd_array[][2], char *input_file);
int			setup_outfile(int fd_array[][2], char *output_file);
int			setup_append_outfile(int fd_array[][2], char *output_file);
int			redirect_out_between_pipes(int fd_array[][2], int cmd_num,
				t_command *cmd);
int			redirect_input_between_pipes(int fd_array[][2], int cmd_num);

// ---stdio_save_restore.c
void		save_stdio(int fd[2]);
void		restore_stdio(int fd[2]);

// ---exec_builtin.c
int			execute_builtin_w_pipe(t_shell *shell, t_command *cmd);
int			execute_builtin(t_shell *shell, t_command *cmd);
int			is_builtin(t_command *cmd);
void		init_fds_pipe4shell(int fd[4][2]);

// ---exec0.c
int			execute_ast(t_shell *shell, t_tree *node, int exit_code);

// ---pipex_wrapper.c
int			pipex_wrapper(t_shell *shell, t_command *cmd);
void		child_sequence(int fd[][2], int index, \
							t_command *cmd, t_shell *shell);
void		close_all_4shell(int fd_array[4][2]);

// -------------------------------------------DIR---expand
// -expand_dollar.c
void		expand_dollar_tokens(t_shell *shell, t_token *token);
void		handle_word_or_dquote(t_shell *shell, t_token *token);
void		process_dollar_token(t_shell *shell, t_token *current, char *str);
char		*expand_word_token(t_shell *shell, const char *str);

// -expand_utils.c
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin_free_char(char *s, char c);
char		*extract_variable_name(const char *str, int *i);
int			handle_quotes(const char *str, int i, int *in_dquote);
char		*expand_variables(t_shell *shell, const char *str,
				int *i, int in_dquote);

// -expand_utils2.c
t_token		*fallback_on_prev_token(t_token *current);
void		handle_single_quote(t_token *token);
void		handle_exit_code(t_shell *shell, t_token *token);
t_token		*wildcard_join(t_token *current);

// -expand_wildcard.c
void		expand_wildcard_tokens(t_shell *shell);
void		expand_wildcard_token(t_shell *shell, t_token *token,
				DIR *dir);
void		handle_wildcard_match(t_shell *shell, t_token *token,
				t_token *prev, bool found_match);
bool		match(char *pattern, char *string);

// -------------------------------------------DIR---loop
// -loop.c
int			shell_loop(t_shell	*shell);
void		*ft_readline(t_shell *shell);
int			handle_input(t_shell *shell);
int			trim_and_free_input(t_shell *shell);

// -loop_further.c
void		*ft_readline_further(t_shell *shell);
int			prompt_further(t_shell *shell);

// -------------------------------------------DIR---parse
// -ast_helper.c
t_token		*get_input_file(t_command *cmd, t_token *start, t_token *stop);
t_token		*get_heredoc(t_command *cmd, t_token *start, t_token *stop);
t_token		*get_output_file(t_command *cmd, t_token *start, t_token *stop);
char		**list_to_arr_no_limit(t_token *start);

// -ast_herlper2.c
t_tree		*add_tree_node_pipe(t_token *pipe_token, t_token *start,
				t_token *stop, t_tree *parent);
t_tree		*add_tree_node_and_or(t_token *head_token, t_token *start,
				t_token *stop, t_tree *parent);
t_token		*get_pivot_token(t_token *current, int *depth, \
						int *head_node_depth, t_token *head_token);
t_token		*process_redirections(t_command *cmd, t_token *current,
				t_token *stop);

// -ast_setup.c
t_tree		*init_cmd_node(t_token *start, t_token *stop, t_tree *parent);
t_tree		*init_tree_node(t_token *token, t_tree *parent);
t_tree		*get_nodes_pipes(t_token *start, t_token *stop, t_tree *parent);
t_tree		*get_nodes_and_or(t_token *start, t_token *stop, t_tree *parent);

// -lexer_utils.c
void		add_token(t_shell *shell, t_tokentype type, char *value);
t_token		*create_token(t_tokentype type, char *value);
void		add_word_token(t_shell *shell, char *input, int start, int end);
void		add_special_token(t_shell *shell, char *special);
void		handle_wildcard_char(t_shell *shell, char *input,
				int *i, int *start);

// -lexer.c
int			tokenize(t_shell *shell, char *input);
void		handle_character(t_shell *shell, char *input, int *i, int *start);
void		handle_quote(t_shell *shell, char *input, int *i, int *start);
void		handle_special_chars(t_shell *shell, char *input,
				int *i, int *start);
void		handle_dollar_char(t_shell *shell, char *input, int *i, int *start);

// -parse.c
int			parse(t_shell *shell);
int			syntax_check(char *input);
int			check_start_end(char *input);
int			quotes_a_parentheses(char *input);
int			check_consecutive_operators(char *input);

// -strip_spaces.c
void		strip_spaces(t_shell *shell);
void		trim_trailing_spaces(t_shell *shell);

// -token_extras.c
void		insert_token(t_shell *shell, t_token *wc_token, \
					t_tokentype type, char *value);

// -utils.c
t_tokentype	get_token_type(char *str);
int			token_count(t_env *env_list);
int			check_redirect_syntax(char *input, int *i);

// -------------------------------------------DIR---prompts
// -prompts.c
void		form_prompt(t_shell *shell, char *new_user_name);
void		print_welcome_msg(void);

// -------------------------------------------DIR---setup
// -init_shell.c
void		init_shell(t_shell *shell, char **env);
void		init_shell_env(t_shell *shell);

// -env.c
t_env		*init_env_list(char **env);
int			add_env_node(t_env **env_list, char *key, char *value);
char		**sync_env_from_list(t_env *env_list, t_shell *shell);
void		update_env_shell(t_shell *shell);

// -------------------------------------------DIR---signals
// -signals.c
void		signal_handlers(void);
void		sigint_handler(int signum);
void		disable_ctrl_chars(void);
void		sigquit_handler(int sig);

// -------------------------------------------DIR---utils
// ---utiles0.c
char		**ft_arrdup(char **arr);
int			ft_isspace(char c);
int			ft_is_special_char(char c);
int			ft_strcmp(const char *str1, const char *str2);

// ---free.c
void		free_env_list(t_env *env_list);
void		free_shell(t_shell *shell, int input_status);
void		free_ast(t_tree *root);
void		free_tokens(t_shell *shell);

#endif

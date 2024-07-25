/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:13 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/25 18:04:34 by mrusu            ###   ########.fr       */
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

// own lib's
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include "structures.h"

// ast_debug
# define GET 0
# define SET 1
# define LEFT -1
# define RIGHT 1
# define DOWN 2
# define UP -2
# define CURRENT_WIDTH 3
# define CURRENT_DEPTH -3

// Colors
# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"
# define RESET "\033[m"

// Typdef

// **********************====FUNCTION DECLARATION====*********************
// main.c

// ----------DIR-----builtins
// ---builtins0.c
void		builtin_echo(char **args);
void		builtin_cd(char **args);
void		builtin_pwd(void);
void		builtin_export(t_shell *shell, char **args);
void		builtin_exit(void);

// ---env.c
void		print_env(t_shell *shell);
int			ft_set_env_node(t_env *env_list, char *key, char *value);
t_env		*ft_unset_env_node(t_env *env_list, char *key);

// ----------DIR-----loop
// -loop.c
int			shell_loop(t_shell	*shell);
void		*ft_readline(t_shell *shell);

// ----------DIR-----setup
// -init_shell.c
void		init_shell(t_shell *shell, char **env);

// -env.c
char		*ft_getenv(void);
t_env		*init_env_node(char *key, char *value);

// ----------DIR-----prompts
// -terminal_prompt.c
void		form_prompt(t_shell *shell, char *new_user_name);

// ----------DIR-----utils
// ---env.c
t_env		*get_tail(t_env *env_list);
t_env		*get_key_node(t_env *env_list, char *key);

// ---utiles0.c
char		**ft_arrdup(char **arr);
int			ft_isspace(char c);
int			ft_is_special_char(char c);
int			ft_strcmp(const char *str1, const char *str2);

// ---wild_math.c
int			my_max(int a, int b);
int			my_min(int a, int b);

// ----------DIR-----error
// -error.c
int			ft_error(t_shell *shell, int error_code);
int			syntax_error(void);

// ----------DIR-----prompts
// -prompts.c
void		print_welcome_msg(void);

// ----------DIR-----parse
// -ast_debug.c
int			print_ast(t_shell *shell);
void		print_ast_recursive1(t_tree *node, int depth);
int			depth_counter(int get_set, int direction, int val);
void		print_ast_recursive2(t_tree *tree);
int			print_ast_recursive2main(t_tree *tree, int is_left, int offset, int depth, char s[20][255]);

// -ast_helper.c
t_token		*get_input_file(t_command *cmd, t_token *start, t_token *stop);
t_token		*get_heredoc(t_command *cmd, t_token *start, t_token *stop);
t_token		*get_output_file(t_command *cmd, t_token *start, t_token *stop);
char		**list_to_arr(t_token *start, t_token *stop);

// -ast_setup.c
t_tree		*init_cmd_node(t_token *start, t_token *stop, t_tree *parent);
t_tree		*init_tree_node(t_token *token, t_tree *parent);
t_tree		*get_nodes_pipes(t_token *start, t_token *stop, t_tree *parent);
t_tree		*get_nodes_and_or(t_token *start, t_token *stop, t_tree *parent);

// -lexer.c
int			tokenize_loop(t_shell *shell, char *input, int i, int start);
void		handle_quote_token(t_shell *shell, char *input, int *i, int *start);
void		handle_special_chars(t_shell *shell, char *input,
				int *i, int *start);
t_token		*create_token(t_tokentype type, char *value);
void		add_token(t_shell *shell, t_tokentype type, char *value);

// -parse.c
int			parse(t_shell *shell);
int			syntax_check(char *input);
int			check_start_end(char *input);
int			quotes_a_parentheses(char *input);
int			check_consecutive_operators(char *input);

// -utils.c
t_tokentype	get_token_type(char *str);
void		free_tokens(t_shell *shell);
void		add_word_token(t_shell *shell, char *input, int start, int end);
int			tokenize(t_shell *shell, char *input);
void		add_special_token(t_shell *shell, char *special);

// ----------DIR-----pipex_wrapper
// -input_formatting.c
int			package_pipex(t_shell *shell);

// ----------DIR-----signals
// -signals.c
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		handle_sigtstp(int sig);
void		set_signal_flag(int in_child_process);
void		setup_signals(void);

#endif

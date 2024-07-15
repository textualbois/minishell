/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:13 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/15 13:13:58 by mrusu            ###   ########.fr       */
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

// own lib's
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include "structures.h"

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

// loop
// ---loop.c
int			shell_loop(t_shell	*shell);
void		*ft_readline(t_shell *shell);

// setup
// ---init_shell.c
void		init_shell(t_shell *shell, char **env);

// ---env.c
char		*ft_getenv(void);

// prompts
// ---terminal_prompt.c
void		form_prompt(t_shell *shell);

// utile
// ---utiles0.c
char		**ft_arrdup(char **arr);
int			ft_isspace(char c);
int			ft_is_special_char(char c);
// error
// ---error.c
int			ft_error(t_shell *shell, int error_code);
int			syntax_error(void);

// prompts
// ---prompts.c
void		display_prompt(void);
void		print_welcome_msg(void);

// parse
// ---execute.c
int			execute_command(t_shell *shell);

// ---lexer.c
int			tokenize(t_shell *shell, char *input);
void		handle_quote_token(t_shell *shell, char *input, int *i, int *start);
void		handle_special_chars(t_shell *shell, char *input,
				int *i, int *start);
void		add_token(t_shell *shell, t_tokentype type, char *value);
void		tokens_to_argv(t_command *cmd, char *arg);
void		handle_token(t_command *cmd, t_token *token);

// ---utils.c
t_tokentype	get_token_type(char *str);
void		free_tokens(t_shell *shell);

// ---parse.c
int			parse(t_shell *shell);
int			quotes_check(t_shell *shell);
void		free_tokens(t_shell *shell);

// pipex_wrapper
// ---input_formatting.c
int			package_pipex(t_shell *shell);

#endif
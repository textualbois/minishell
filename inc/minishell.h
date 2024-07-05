/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:13 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/05 16:09:14 by mrusu            ###   ########.fr       */
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

// own lib's
# include "../libft/libft.h"
# include "../pipex/pipex.h"

// Colors
# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"
# define RESET "\033[m"

// Typdef

// Forward declaration of structs

// code for tokentype
typedef enum e_tokentype
{
	T_WORD, // word
	T_PIPE, // | 
	T_REDIRECT_IN, // <
	T_REDIRECT_OUT, // >
	T_REDIRECT_APPEND, // >>
	T_HEREDOC, // <<
}	t_tokentype;

// **********************====STRUCT====*********************
// Strucutre for token
typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

typedef struct s_command
{
	char	**args;
	char	*name;
	char	*input_file;
	char	*output_file;
	char	*heredoc_delimiter;
	int		append_output;
	int		pipe_in; //store fd for in
	int		pipe_out; // for out
}	t_command;

// Strucutre for data
typedef struct s_data
{
	char		**av;
	char		**env;
	char		**path;
	char		*pwd;
	int			pipes;
	int			*pid;
	int			token_count;
	int			command_count; // keep track of number of commands in curent pipe
	int			exit_status; //store exit status for $?
	char		*input_line; // store original input line , for error or history
	t_token		*tokens;
	t_command	**commands;
}	t_data;

// **********************====FUNCTION DECLARATION====*********************
// main.c

// utile
// ---utiles0.c
char	**ft_arrdup(char **arr);

// error.c
int		ft_error(t_data *data, int error_code);
int		syntax_error(void);

void display_prompt(void);
char *read_input(void);
void print_welcome_msg(void);
int loop(t_data *data);



// lexer.c


//parse.c

#endif
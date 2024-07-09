/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:32:24 by isemin            #+#    #+#             */
/*   Updated: 2024/07/09 15:41:11 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// main shell object
typedef struct s_shell //todo
{
	char	*terminal_prompt;
	char	*input_prompt;
	int		exit_code;
	char	*user;
	char	**env;
}	t_shell;

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

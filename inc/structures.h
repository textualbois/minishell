/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:32:24 by isemin            #+#    #+#             */
/*   Updated: 2024/07/11 19:09:10 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Forward declaration of structs
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_pipex		t_pipex;
typedef struct s_shell		t_shell;

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
	char		*terminal_prompt;
	char		*raw_input;
	int			exit_code;
	char		*user;
	char		**env;
	char		*heredoc;
	char		*last_input;
	int			stdio_fds[2];
	char		**cmd_paths;
	char		**path;
	char		*pwd;
	int			pipes;
	int			*pid;
	int			token_count; // the number of tokens in the current input
	int			command_count; // keep track of number of commands in current pipe
	int			token_capacity; // the capacity of the tokens array
	t_token		*tokens; // array of tokens
	t_command	**commands;
	t_pipex		**pipex;
}	t_shell;

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int		is_heredoc;
	char	*heredoc_delimiter;
	int		append_output;
	char	**cmds;
	char	**flags;
}	t_pipex;

// Strucutre for storing tokens
// value: the actual token value
// type: the type of token (enum t_tokentype)
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

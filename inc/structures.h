/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:32:24 by isemin            #+#    #+#             */
/*   Updated: 2024/07/10 11:03:30 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Forward declaration of structs
typedef struct s_token		t_token;
typedef struct s_command	t_command;

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
	char	*raw_input;
	int		exit_code;
	char	*user;
	char	**env;
	char	*heredoc;
	char	*last_input;
	int		stdio_fds[2];
	char	**cmd_paths;

    // Additional fields from t_data
	char		**path;
	char		*pwd;
	int			pipes;
	int			*pid;
	int			token_count;
	int			command_count; // keep track of number of commands in current pipe
	t_token		*tokens;
	t_command	**commands;
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

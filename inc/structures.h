/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:32:24 by isemin            #+#    #+#             */
/*   Updated: 2024/08/09 13:31:38 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Forward declaration of structs
typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_pipex		t_pipex;
typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef struct s_tree		t_tree;

// code for tokentype
typedef enum e_tokentype
{
	T_WORD,
	T_SPECIAL,
	T_PIPE,
	T_OR,
	T_AND,
	T_SPACE,
	T_WILDCARD,
	T_WORD_EXPAND,
	T_DOLLAR,
	T_EXCODE,
	T_SQUOTE,
	T_DQUOTE
}	t_tokentype;

// **********************====STRUCT====*********************

// main shell object
typedef struct s_shell
{
	char		*terminal_prompt;
	char		*input;
	int			exit_code;
	char		*user;
	t_env		*env_list;
	char		**env;
	char		*heredoc;
	char		*last_input;
	int			stdio_fds[2];
	char		**cmd_paths;
	char		**path;
	char		*pwd;
	int			pipes;
	int			*pid;
	int			token_count;
	int			command_count;
	t_token		*head;
	t_token		*tail;
	t_tree		*ast;
	t_command	**commands;
	t_pipex		**pipex;
}	t_shell;

typedef struct s_env
{
	t_env	*next;
	char	*key;
	char	*value;
}	t_env;

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

/*
* @brief: Structure for storing tokens.
* @param value: the actual token value
* @param type: the type of token (enum t_tokentype)
*/
typedef struct s_token
{
	char	*value;
	int		type;
	t_token	*next;
	t_token	*prev;
}	t_token;

typedef struct s_command
{
	char		**args;
	char		*name;
	char		*input_file;
	char		*output_file;
	char		*heredoc_delimiter;
	int			append_output;
	int			pipe_in;
	int			pipe_out;
	t_command	*next;
}	t_command;

// Structure for the abstract syntax tree
typedef struct s_tree
{
	t_command	*cmd;
	t_tree		*left;
	t_tree		*right;
	t_tree		*parent;
	t_token		*token;
}	t_tree;

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:34:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/11 20:03:59 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Tokenizes the input string, creating tokens for each word,
*	pipe, redirection, or heredoc operator.
*/
int	tokenize(t_shell *shell, char *input)
{
	int	i;
	int	start;

	shell->tokens = NULL;
	shell->token_count = 0;
	i = -1;
	start = 0;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
			handle_quote_token(shell, input, &i, &start);
		else if (ft_isspace(input[i]) || ft_is_special_char(input[i]))
			handle_special_chars(shell, input, &i, &start);
	}
	if (i > start)
		add_token(shell, T_WORD, ft_substr(input, start, i - start));
	return (0);
}

/*
* @ brief: Processes quoted strings in the input string,
*	capturing the quoted string and creating a token for it.
*/
void	handle_quote_token(t_shell *shell, char *input, int *i, int *start)
{
	static int	in_quote;
	static char	current_quote;

	in_quote = 0;
	current_quote = 0;
	if (!in_quote)
	{
		if (*i > *start)
			add_token(shell, T_WORD, ft_substr(input, *start, *i - *start));
		in_quote = 1;
		current_quote = input[*i];
		*start = *i + 1;
	}
	else if (input[*i] == current_quote)
	{
		add_token(shell, T_WORD, ft_substr(input, *start, *i - *start));
		in_quote = 0;
		*start = *i + 1;
	}
}

/*
* @ brief: Processes special characters in the input string, 
*	creating tokens for them and updating the token start index.
*/
void	handle_special_chars(t_shell *shell, char *input, int *i, int *start)
{
	if (*i > *start)
		add_token(shell, get_token_type(input + *start),
			ft_substr(input, *start, *i - *start));
	if (ft_is_special_char(input[*i]))
	{
		if (input[*i] == '>' && input[*i + 1] == '>')
		{
			add_token(shell, T_REDIRECT_APPEND, ft_strdup(">>"));
			(*i)++;
		}
		else if (input[*i] == '<' && input[*i + 1] == '<')
		{
			add_token(shell, T_HEREDOC, ft_strdup("<<"));
			(*i)++;
		}
		else
		{
			add_token(shell, get_token_type(input + *i),
				ft_substr(input, *i, 1));
		}
	}
	*start = *i + 1;
}

/*
* @ brief: Adds a new token to the shell's token list.
*/
void	add_token(t_shell *shell, t_tokentype type, char *value)
{
	t_token	*new_tokens;
	int		i;

	new_tokens = malloc(sizeof(t_token) * (shell->token_count + 1));
	if (!new_tokens)
		return ;
	i = -1;
	while (++i < shell->token_count)
	{
		new_tokens[i] = shell->tokens[i];
	}
	new_tokens[i].type = type;
	new_tokens[i].value = value;
	free(shell->tokens);
	shell->tokens = new_tokens;
	shell->token_count++;
}

/*
* @ brief: Determines the type of a token based on char.
*/
t_tokentype	get_token_type(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (T_PIPE);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (T_REDIRECT_IN);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (T_REDIRECT_OUT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (T_HEREDOC);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (T_REDIRECT_APPEND);
	else
		return (T_WORD);
}

/*
* @ brief: Adds a new argument to the command's argument list.
*	convert tokens to char **args so we can execve
*/
void	tokens_to_argv(t_command *cmd, char *arg)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	j = 0;
	while (i > j)
	{
		new_args[j] = cmd->args[j];
		j++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

/*
* @ brief: Processes a token, shuld execut the command
*/
void	handle_token(t_command *cmd, t_token *token)
{
	if (token->type == T_WORD)
		tokens_to_argv(cmd, token->value);
	else if (token->type == T_PIPE)
	{
		cmd->pipe_out = 1;
	}
	else if (token->type == T_REDIRECT_IN)
	{
		cmd->input_file = token->value;
	}
	else if (token->type == T_REDIRECT_OUT)
	{
		cmd->output_file = token->value;
	}
	else if (token->type == T_HEREDOC)
	{
		cmd->heredoc_delimiter = token->value;
	}
	else if (token->type == T_REDIRECT_APPEND)
	{
		cmd->append_output = 1;
		cmd->output_file = token->value;
	}
}

void	free_tokens(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->token_count)
		free(shell->tokens[i].value);
	free(shell->tokens);
	shell->tokens = NULL;
	shell->token_count = 0;
}
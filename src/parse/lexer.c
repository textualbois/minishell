/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:34:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/17 12:36:42 by mrusu            ###   ########.fr       */
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
		{
			handle_quote_token(shell, input, &i, &start);
		}
		else if (ft_isspace(input[i]))
		{
			if (i > start)
			{
				add_token(shell, T_WORD, ft_substr(input, start, i - start));
			}
			start = i + 1;
		}
		else if (ft_is_special_char(input[i]))
		{
			handle_special_chars(shell, input, &i, &start);
		}
	}
	if (i > start)
	{
		add_token(shell, T_WORD, ft_substr(input, start, i - start));
	}
	return (0);
}

/*
* @ brief: Processes quoted strings in the input string,
*	capturing the quoted string and creating a token for it.
*/
void	handle_quote_token(t_shell *shell, char *input, int *i, int *start)
{
	char	quote_char;
	int		j;

	quote_char = input[*i];
	j = *i + 1;
	while (input[j] && input[j] != quote_char)
		j++;
	if (input[j] == quote_char)
	{
		j++;
		add_token(shell, T_WORD, ft_substr(input, *i, j - *i));
		*i = j - 1;
		*start = j;
	}
	else
	{
		printf("Error: unmatched quote\n");
	}
}

/*
* @ brief: Processes special characters in the input string, 
*	creating tokens for them and updating the token start index.
*/
void	handle_special_chars(t_shell *shell, char *input, int *i, int *start)
{
	char		special[3];
	t_tokentype	type;

	special[0] = input[*i];
	special[1] = '\0';
	special[2] = '\0';
	if (*i > *start)
		add_token(shell, T_WORD, ft_substr(input, *start, *i - *start));
	type = get_token_type(input + *i);
	if (type != T_WORD)
	{
		if ((type == T_OR || type == T_AND) && input[*i + 1])
		{
			special[1] = input[*i + 1];
			(*i)++;
		}
		add_token(shell, type, special);
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
	{
		printf("Error: malloc failed in add_token\n");
		return ;
	}
	i = -1;
	while (++i < shell->token_count)
	{
		new_tokens[i] = shell->tokens[i];
	}
	new_tokens[i].type = type;
	new_tokens[i].value = ft_strdup(value);
	if (!new_tokens[i].value)
	{
		printf("Error: ft_strdup failed in add_token\n");
		free(new_tokens);
		return ;
	}
	free(shell->tokens);
	shell->tokens = new_tokens;
	shell->token_count++;
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

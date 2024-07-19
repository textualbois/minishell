/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:34:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/19 09:40:43 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Tokenizes the input string, creating tokens for each word,
*	pipe, redirection, or heredoc operator.
*/
int	tokenize(t_shell *shell, char *input)
{
	int		i;
	int		start;
	char	*substr;

	shell->head = NULL;
	shell->tail = NULL;
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
				substr = ft_substr(input, start, i - start);
				add_token(shell, T_WORD, substr);
				free(substr);
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
		substr = ft_substr(input, start, i - start);
		add_token(shell, T_WORD, substr);
		free(substr);
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
		if (input[*i + 1] == input[*i])
		{
			special[1] = input[*i];
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

	new_tokens = malloc(sizeof(t_token) * (shell->token_count + 1));
	if (!new_tokens)
	{
		printf("Error: malloc failed in add_token\n");
		return ;
	}
	new_tokens->type = type;
	new_tokens->value = ft_strdup(value);
	if (!new_tokens->value)
	{
		printf("Error: ft_strdup failed in add_token\n");
		free(new_tokens);
		return ;
	}
	new_tokens->next = NULL;
	new_tokens->prev = shell->tail;
	if (shell->tail)
		shell->tail->next = new_tokens;
	else
		shell->head = new_tokens;
	shell->tail = new_tokens;
	shell->token_count++;
	//debug
	printf("Added Token: Type = ");
	if (type == T_WORD)
		printf("WORD");
	else if (type == T_PIPE)
		printf("PIPE");
	else if (type == T_OR)
		printf("OR");
	else if (type == T_AND)
		printf("AND");
	else if (type == T_SPECIAL)
		printf("SPECIAL");
	else
		printf("UNKNOWN");
	printf(", Value = '%s'\n", value);
}

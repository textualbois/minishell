/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:34:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/30 18:42:25 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Loops through the input string, creating tokens for each part.
*/
int	tokenize_loop(t_shell *shell, char *input, int i, int start)
{
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			handle_quote_token(shell, input, &i, &start);
		else if (ft_isspace(input[i]))
		{
			if (i > start)
				add_word_token(shell, input, start, i);
			start = i + 1;
		}
		else if (ft_is_special_char(input[i]))
			handle_special_chars(shell, input, &i, &start);
		else if (input[i] == '$')
			handle_dollar_char(shell, input, &i, &start);
		else if (input[i] == '*')
			handle_wildcard_char(shell, input, &i, &start);
		i++;
	}
	if (i > start)
		add_word_token(shell, input, start, i);
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
	char	*substr;

	quote_char = input[*i];
	j = *i + 1;
	while (input[j] && input[j] != quote_char)
		j++;
	if (input[j] == quote_char)
	{
		j++;
		substr = ft_substr(input, *i, j - *i);
		add_token(shell, T_WORD, substr);
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
		add_word_token(shell, input, *start, *i);
	type = get_token_type(input + *i);
	if (special[0] == '$' && input[*i + 1] == '?')
	{
		add_token(shell, T_EXCODE, ft_strdup("$?"));
		(*i)++;
	}
	else if ((special[0] == '|' && input[*i + 1] == '|')
		|| (special[0] == '&' && input[*i + 1] == '&')
		|| (special[0] == '>' && input[*i + 1] == '>')
		|| (special[0] == '<' && input[*i + 1] == '<'))
	{
		special[1] = input[*i + 1];
		(*i)++;
	}
	add_special_token(shell, special);
	*start = *i + 1;
}

/*
* @ brief: Adds a new token to the shell's token list.
*	call create_token and pass the type and value to it
*	then add the token to the end of the shell's token list
*/
void	add_token(t_shell *shell, t_tokentype type, char *value)
{
	t_token	*new_token;

	new_token = create_token(type, value);
	if (!new_token)
		return ;
	if (shell->head == NULL)
	{
		shell->head = new_token;
		shell->tail = new_token;
	}
	else
	{
		shell->tail->next = new_token;
		new_token->prev = shell->tail;
		shell->tail = new_token;
	}
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
	else if (type == T_DOLLAR)
		printf("DOLLAR");
	else if (type == T_EXCODE)
		printf("$?");
	else if (type == T_WILDCARD)
		printf("WILDCARD");
	else
		printf("UNKNOWN");
	printf(", Value = '%s'\n", value);
}

/*
* @ brief: Creates a new token with given type and value.
*	and puts it at the end of the shell's token list.
*/
t_token	*create_token(t_tokentype type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token) * 1);
	if (!new_token)
	{
		printf("Error: malloc failed in create_token\n");
		return (NULL);
	}
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		printf("Error: ft_strdup failed in create_token\n");
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

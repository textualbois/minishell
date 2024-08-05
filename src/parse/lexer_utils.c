/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:57:50 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/05 13:50:51 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: initializes the shell's token list and token count.
*/
int	tokenize(t_shell *shell, char *input)
{
	shell->head = NULL;
	shell->tail = NULL;
	shell->token_count = 0;
	if (tokenize_loop(shell, input, 0, 0) != 0)
	{
		printf("Error: tokenize_loop failed\n");
		return (1);
	}
	return (0);
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
	else if (type == T_WORD_EXPAND)
		printf("T_WORD_EXPAND");
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

/*
* brief: adds only word tokens type to the shell's token list.
*/
void	add_word_token(t_shell *shell, char *input, int start, int end)
{
	char	*substr;

	substr = ft_substr(input, start, end - start);
	if (!substr)
	{
		printf("Error: ft_substr failed in add_word_token\n");
		return ;
	}
	add_token(shell, T_WORD, substr);
	free(substr);
}

/*
* @ brief: adds special tokens to the shell's token list by special char.
*/
void	add_special_token(t_shell *shell, char *special)
{
	if (special[0] == '|')
	{
		if (special[1] == '|')
			add_token(shell, T_OR, special);
		else
			add_token(shell, T_PIPE, special);
	}
	else if (special[0] == '&')
	{
		if (special[1] == '&')
			add_token(shell, T_AND, special);
		else
			add_token(shell, T_WORD, special);
	}
	else if (special[0] == '$')
		add_token(shell, T_DOLLAR, special);
	else
		add_token(shell, T_SPECIAL, special);
}

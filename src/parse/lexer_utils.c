/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:57:50 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/13 13:04:40 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char		*word;
	t_tokentype	type;

	type = T_WORD;
	word = ft_substr(input, start, end - start);
	if (ft_strchr(word, '$'))
		type = T_WORD_EXPAND;
	add_token(shell, type, word);
	free(word);
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

/*
* @ brief : Adds a WILDCARD token to the shell's token list.
*/
void	handle_wildcard_char(t_shell *shell, char *input, int *i, int *start)
{
	int		j;
	char	*substr;

	j = *i + 1;
	while (input[j] && !ft_isspace(input[j]) && !ft_is_special_char(input[j]))
		j++;
	substr = ft_substr(input, *i, j - *i);
	add_token(shell, T_WILDCARD, substr);
	*i = j - 1;
	*start = j;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:05:39 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/30 13:11:34 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Determines the type of a token based on char.
*/
t_tokentype	get_token_type(char *str)
{
	if (*str == '|')
	{
		if (*(str + 1) == '|')
			return (T_OR);
		else
			return (T_PIPE);
	}
	else if (*str == '&' || (*str == '&' && *(str + 1) == '&'))
		return (T_AND);
	else if (*str == '<' || (*str == '<' && *(str + 1) == '<'))
		return (T_SPECIAL);
	else if (*str == '>' || (*str == '>' && *(str + 1) == '>'))
		return (T_SPECIAL);
	else if (*str == '"' || *str == '\'')
		return (T_QUOTE);
	else if (*str == '$' && *(str + 1) == '?')
		return (T_EXCODE);
	else if (*str == '$')
		return (T_DOLLAR);
	else
		return (T_WORD);
}

/*
* @ brief: clears the shell's token list.
*/
void	free_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	shell->head = NULL;
	shell->tail = NULL;
	shell->token_count = 0;
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
* @ brief: adds special tokens to the shell's token list.
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

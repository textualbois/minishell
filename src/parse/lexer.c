/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:34:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/14 21:28:44 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: initializes the shell's token list and token count.
*	Calls handle_character for each character in the input string.
* 	When the loop ends, if there are characters left, add a word token.
*/
int	tokenize(t_shell *shell, char *input)
{
	int		i;
	int		start;

	shell->head = NULL;
	shell->tail = NULL;
	shell->token_count = 0;
	i = 0;
	start = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (i > start)
				add_word_token(shell, input, start, i);
			handle_quote(shell, input, &i, &start);
		}
		else
			handle_character(shell, input, &i, &start);
		i++;
	}
	if (i > start)
		add_word_token(shell, input, start, i);
	return (0);
}

/*
* @ brief: Creates a token for a input based on the character type.
*/
void	handle_character(t_shell *shell, char *input, int *i, int *start)
{
	char	*temp;

	if (ft_isspace(input[*i]))
	{
		if (*i > *start)
			add_word_token(shell, input, *start, *i);
		*start = *i + 1;
		temp = ft_strdup("");
		add_token(shell, T_SPACE, temp);
		free(temp);
	}
	else if (ft_is_special_char(input[*i]))
	{
		if (*i > *start)
			add_word_token(shell, input, *start, *i);
		handle_special_chars(shell, input, i, start);
	}
	else if (input[*i] == '$')
	{
		if (*i > *start)
			add_word_token(shell, input, *start, *i);
		handle_dollar_char(shell, input, i, start);
	}
}

/*
* @ brief: adds nokens with qoutes based on the quote type.
* 	Extracts the substr in the quotes and creates a token with it.
*/
void	handle_quote(t_shell *shell, char *input, int *i, int *start)
{
	char		quote;
	int			j;
	t_tokentype	type;
	char		*temp;

	quote = input[*i];
	j = *i + 1;
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] == quote)
	{
		if (quote == '"')
			type = T_DQUOTE;
		else
			type = T_SQUOTE;
		temp = ft_substr(input, *i + 1, j - (*i + 1));
		add_token(shell, type, temp);
		free(temp);
		*i = j;
		*start = j + 1;
	}
	else
		return (printf("Teoretically: Never gonna give you up,\n"), (void)42);
}

/*
* @ brief: Processes special characters in the input string,
*	creating tokens for them and updating the token start index.
*/
void	handle_special_chars(t_shell *shell, char *input, int *i, int *start)
{
	char		special[3];

	special[0] = input[*i];
	special[1] = '\0';
	special[2] = '\0';
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
* @ brief: Check the following character after the $, if it's
*	'?' add a T_EXCODE token, otherwise, get the variable name
*	that is after and add a T_DOLLAR token.
*/
void	handle_dollar_char(t_shell *shell, char *input, int *i, int *start)
{
	int		j;
	char	*var_name;

	if (input[*i + 1] == '?')
	{
		add_token(shell, T_EXCODE, ft_strdup("?"));
		(*i)++;
	}
	else
	{
		j = *i + 1;
		while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
			j++;
		var_name = ft_substr(input, *i + 1, j - (*i + 1));
		if (var_name)
		{
			add_token(shell, T_DOLLAR, var_name);
			free(var_name);
		}
		*i = j - 1;
	}
	*start = *i + 1;
}

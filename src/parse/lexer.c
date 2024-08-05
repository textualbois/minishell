/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:34:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/05 15:35:34 by mrusu            ###   ########.fr       */
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
		if (input[i] == '\'')
			handle_squote(shell, input, &i, &start);
		else if (input[i] == '"')
			handle_dquote(shell, input, &i, &start);
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
* brief: Processes single quoted strings in the input string,
*	capturing the quoted string and creating a token for it.
*/
void	handle_squote(t_shell *shell, char *input, int *i, int *start)
{
	int		j;
	char	*substr;

	j = *i + 1;
	while (input[j] && input[j] != '\'')
		j++;
	if (input[j] == '\'')
	{
		substr = ft_substr(input, *i + 1, j - *i - 1);
		add_token(shell, T_WORD, substr);
		free(substr);
		*i = j;
		*start = j + 1;
	}
	else
	{
		printf("Teoretically: Never gonna give you up,\n");
		printf("never gonna let you down,\n");
		printf("never gonna run around and desert you.\n");
		return ;
	}
}

/*
* brief: Processes double quoted strings in the input string,
*	capturing the quoted string and creating a token for it.
*/
void	handle_dquote(t_shell *shell, char *input, int *i, int *start)
{
	int		j;
	char	*substr;

	j = *i + 1;
	while (input[j] && input[j] != '\"')
		j++;
	if (input[j] == '\"')
	{
		substr = ft_substr(input, *i + 1, j - *i - 1);
		add_token(shell, T_WORD_EXPAND, substr);
		free(substr);
		*i = j;
		*start = j + 1;
	}
	else
	{
		printf("Teoretically: Never gonna give you up,\n");
		printf("never gonna let you down,\n");
		printf("never gonna run around and desert you.\n");
		return ;
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

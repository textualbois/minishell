/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:57:00 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/09 15:14:58 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Expands the dollar tokens by replacing them with the value of the
*	variables they represent, based on tokens type.
*/
void	expand_dollar_tokens(t_shell *shell)
{
	t_token	*current;
	char	*exp;

	current = shell->head;
	while (current)
	{
		if (current->type == T_WORD_EXPAND || current->type == T_DQUOTE)
			handle_word_or_dquote(shell, current);
		else if (current->type == T_SQUOTE)
		{
			exp = ft_substr(current->value, 1, ft_strlen(current->value) - 2);
			free(current->value);
			current->value = exp;
			current->type = T_WORD;
		}
		else if (current->type == T_DOLLAR)
			process_dollar_token(shell, current);
		else if (current->type == T_EXCODE)
		{
			free(current->value);
			current->value = ft_itoa(shell->exit_code);
			current->type = T_WORD;
		}
		current = current->next;
	}
}

/*
* @ brief: Handles a T_WORD_EXPAND or T_DQUOTE token by expanding the word.
*/
void	handle_word_or_dquote(t_shell *shell, t_token *token)
{
	char	*expanded;

	expanded = expand_word_token(shell, token->value);
	free(token->value);
	token->value = expanded;
	token->type = T_WORD;
}

/*
* @ brief: Processes a T_DOLLAR token by getting the value of the variable
*	and replacing the token with a T_WORD token and the value.
*/
void	process_dollar_token(t_shell *shell, t_token *token)
{
	char	*value;

	value = get_env_value(shell->env_list, token->value);
	free(token->value);
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = ft_strdup("");
	token->type = T_WORD;
}

/*
* @ brief: Expands a word by replacing the variables with their values.
*/
char	*expand_word_token(t_shell *shell, const char *str)
{
	char	*result;
	int		i;
	int		in_dquote;
	char	*expanded;

	i = 0;
	in_dquote = 0;
	result = ft_strdup("");
	while (str[i])
	{
		i = handle_quotes(str, i, &in_dquote);
		if (str[i] != '"')
		{
			expanded = expand_variables(shell, str, &i, in_dquote);
			result = ft_strjoin_free(result, expanded);
			free(expanded);
		}
	}
	return (result);
}

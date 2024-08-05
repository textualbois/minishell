/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:57:00 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/05 13:17:56 by mrusu            ###   ########.fr       */
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
	char	*value;
	char	*expanded;

	current = shell->head;
	while (current)
	{
		if (current->type == T_DOLLAR)
			process_dollar_token(shell, current);
		else if (current->type == T_WORD_EXPAND)
		{
			expanded = expand_word_token(shell, current->value);
			free(current->value);
			current->value = expanded;
			current->type = T_WORD;
		}
		else if (current->type == T_EXCODE)
		{
			value = ft_itoa(shell->exit_code);
			free(current->value);
			current->value = value;
			current->type = T_WORD;
		}
		current = current->next;
	}
}

/*
* @ brief: Expands a word by replacing the variables with their values.
*	Iterates through the string, if it finds a $, it extracts the variable name
*	and gets the value from the environment list. If the value is found, it
*	joins it to the result string, otherwise, it joins an empty string.
*	Otherwise, it joins the character to the result string.
*/
char	*expand_word_token(t_shell *shell, char *str)
{
	char	*result;
	char	*value;
	char	*var_name;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = extract_variable_name(str, &i);
			value = get_env_value(shell->env_list, var_name);
			if (value)
				result = ft_strjoin_free(result, value);
			else
				result = ft_strjoin_free(result, "");
			free(var_name);
		}
		else
		{
			result = ft_strjoin_free_char(result, str[i++]);
		}
	}
	return (result);
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
		value = ft_strdup(value);
	else
		value = ft_strdup("");
	token->type = T_WORD;
}

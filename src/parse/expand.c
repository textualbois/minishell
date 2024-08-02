/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:57:00 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/02 17:54:20 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

// Helper function to join strings and free the first one
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

// Helper function to join a string and a char, freeing the string
char	*ft_strjoin_free_char(char *s, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(s, tmp));
}

char	*expand_word(t_shell *shell, char *str) //refac
{
	char	*result;
	char	*value;
	char	*var_name;
	int		i;
	int 	j;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			var_name = ft_substr(str, i + 1, j - i - 1);
			value = get_env_value(shell->env_list, var_name);
			result = ft_strjoin_free(result, value ? value : "");
			free(var_name);
			i = j;
		}
		else
		{
			result = ft_strjoin_free_char(result, str[i]);
			i++;
		}
	}
	return (result);
}

/*
* @ brief: Expands DOLLAR tokens to their corresponding values.
*	or to an empty string if the variable is not found.
*	if it's a $?, expand and print to the exit code.
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
		{
			value = get_env_value(shell->env_list, current->value);
			free(current->value);
			current->value = value ? ft_strdup(value) : ft_strdup("");
			current->type = T_WORD;
		}
		else if (current->type == T_WORD_EXPAND)
		{
			expanded = expand_word(shell, current->value);
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



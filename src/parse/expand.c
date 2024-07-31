/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:57:00 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/31 16:27:58 by isemin           ###   ########.fr       */
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

/*
* @ brief: Expands DOLLAR tokens to their corresponding values.
*	or to an empty string if the variable is not found.
*	if it's a $?, expand and print to the exit code.
*/
void	expand_dollar_tokens(t_shell *shell)
{
	t_token	*current;
	char	*value;

	current = shell->head;
	while (current)
	{
		if (current->type == T_DOLLAR)
		{
			value = get_env_value(shell->env_list, current->value);
			free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = ft_strdup("");
			current->type = T_WORD;
		}
		else if (current->type == T_EXCODE)
		{
			value = ft_itoa(shell->exit_code);
			free(current->value);
			current->value = value;
			// printf("%d\n", shell->exit_code);
			current->type = T_WORD;
		}
		current = current->next;
	}
}

/*
* @ Brief: go through the token list, if the token is a wildcard,
*	open the current directory and go through each entry, if the entry
*	matches the wildcard pattern, add a WORD token with the entry name.
*	close the directory and free the wildcard token. move to the next token.
*/
void	expand_wildcard_tokens(t_shell *shell)
{
	t_token			*current;
	DIR				*dir;
	struct dirent	*entry;

	current = shell->head;
	while (current)
	{
		if (current->type == T_WILDCARD)
		{
			dir = opendir(".");
			if (dir)
			{
				while (entry != NULL)
				{
					if (match(current->value, entry->d_name))
						add_token(shell, T_WORD, ft_strdup(entry->d_name));
					entry = readdir(dir);
				}
				closedir(dir);
			}
			free(current->value);
			current->value = NULL;
		}
		current = current->next;
	}
}

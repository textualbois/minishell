/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:57:00 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/30 11:03:40 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Adds a DOLLAR token to the shell's token list.
*/
void	handle_dollar_char(t_shell *shell, char *input, int *i, int *start)
{
	int		j;
	char	*var_name;

	j = *i + 1;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	var_name = ft_substr(input, *i + 1, j - (*i + 1));
	add_token(shell, T_DOLLAR, var_name);
	free(var_name);
	*i = j - 1;
	*start = j;
}

/*
* @ brief: Expands DOLLAR tokens to their corresponding values.
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
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			else
			{
				free(current->value);
				current->value = ft_strdup("");
			}
		}
		current = current->next;
	}
}

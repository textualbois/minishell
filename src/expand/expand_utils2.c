/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:48:53 by isemin            #+#    #+#             */
/*   Updated: 2024/08/15 03:07:27 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_exit_code(t_shell *shell, t_token *token)
{
	free(token->value);
	token->value = ft_itoa(shell->exit_code);
	token->type = T_WORD;
}

void	handle_single_quote(t_token *token)
{
	char	*new_value;

	new_value = ft_substr(token->value, 0, ft_strlen(token->value));
	free(token->value);
	token->value = new_value;
	token->type = T_WORD;
}

t_token	*fallback_on_prev_token(t_token *current)
{
	char	*new_value;
	t_token	*prev;

	prev = current->prev;
	if (prev != NULL && (prev->type == T_SPACE || prev->type == T_WORD))
	{
		new_value = ft_strjoin(prev->value, current->value);
		free(prev->value);
		prev->value = new_value;
		prev->next = current->next;
		if (current->next != NULL)
			current->next->prev = prev;
		free(current->value);
		free(current);
		return (prev);
	}
	return (current);
}

t_token	*wildcard_join(t_token *current)
{
	t_token	*prev;

	prev = current->prev;
	current = fallback_on_prev_token(current);
	if (current->next != NULL && (current->next->type == T_WORD))
		current = fallback_on_prev_token(current->next);
	current->type = T_WILDCARD;
	return (current);
}

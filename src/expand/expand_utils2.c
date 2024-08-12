/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:48:53 by isemin            #+#    #+#             */
/*   Updated: 2024/08/12 10:48:57 by isemin           ###   ########.fr       */
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
	free(token->value);
	token->value = ft_substr(token->value, 1, ft_strlen(token->value) - 2);
	token->type = T_WORD;
}

t_token	*fallback_on_prev_token(t_token *current)
{
	char	*new_value;
	t_token	*prev;

	prev = current->prev;
	if (prev != NULL && (prev->type == T_SPACE || prev->type == T_WORD)) // is the second half of the condition correct? maybe we should fallback to other types as well
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
	// it's always fine to fallback, because dollar tokens dont fall forward
	current = fallback_on_prev_token(current);
	// do not join forward if current->next was a T_SPACE
	// because if current->next->next was a $ token, it made a fallback. if the fallback
	// was made on to a T_SPACE, we should keep the space between intact
	if (current->next != NULL && (current->next->type == T_WORD)) // is this condition correct? what can we join to?
		current = fallback_on_prev_token(current->next);
	current->type = T_WILDCARD;
	return (current);
}

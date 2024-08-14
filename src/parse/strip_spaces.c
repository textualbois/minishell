/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:23:40 by isemin            #+#    #+#             */
/*   Updated: 2024/08/14 21:29:31 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	remove_token(t_shell *shell, t_token *current)
{
	t_token	*temp;

	temp = current;
	if (current->next != NULL && current->prev != NULL)
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
	}
	if (temp->prev == NULL && temp->next != NULL)
	{
		shell->head = temp->next;
		current->next->prev = NULL;
	}
	if (temp->prev != NULL && temp->next == NULL)
	{
		shell->tail = current->prev;
		current->prev->next = NULL;
	}
	current = current->next;
	free(temp->value);
	free(temp);
	temp = NULL;
	shell->token_count--;
}

void	strip_spaces(t_shell *shell)
{
	t_token	*current;
	t_token	*temp;

	current = shell->head;
	while (current)
	{
		if (current->type == T_SPACE)
		{
			temp = current->next;
			if (current->value[0] == '\0' || current->value[0] == ' ')
				remove_token(shell, current);
			else
				current->type = T_WORD;
			current = temp;
		}
		else
			current = current->next;
	}
}

/*
* @ brief: Trims the trailing spaces from the token list.
*/
void	trim_trailing_spaces(t_shell *shell)
{
	t_token	*current;
	t_token	*tmp;

	current = shell->tail;
	while (current && current->type == T_SPACE)
	{
		tmp = current;
		current = current->prev;
		if (current)
			current->next = NULL;
		else
			shell->head = NULL;
		remove_token(shell, tmp);
	}
}

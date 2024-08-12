/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:13:29 by isemin            #+#    #+#             */
/*   Updated: 2024/08/12 09:41:37 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	insert_token(t_shell *shell, t_token *wc_token, \
					t_tokentype type, char *value)
{
	t_token	*token;

	token = create_token(type, value);
	token->type = T_WORD;
	if (!token)
		return ;
	if (shell->head == NULL)
	{
		shell->head = token;
		shell->tail = token;
	}
	else if (wc_token == shell->head)
	{
		shell->head = token;
		token->next = wc_token;
		wc_token->prev = token;
	}
	else
	{
		wc_token->prev->next = token;
		token->prev = wc_token->prev;
		token->next = wc_token;
		wc_token->prev = token;
	}
	shell->token_count++;
}

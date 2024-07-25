/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:20:20 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/25 18:11:33 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_ast(t_shell *shell, t_tree *node)
{
	(void)shell;
	if (!node)
		return (1);
	if (node->cmd)
	{
		// execute_command(shell, node->cmd);
	}
	else if (node->token->type == T_PIPE)
	{
		// execute_pipe(shell, node);
	}
	else if (node->token->type == T_OR)
	{
		// execute_or(shell, node);
	}
	else if (node->token->type == T_AND)
	{
		// execute_and(shell, node);
	}
	return (0);
}

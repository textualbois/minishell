/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:20:20 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/26 18:11:11 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_ast(t_shell *shell, t_tree *node, int exit_code)
{
	(void)shell;
	if (!node)
		return (1);
	if (node->cmd)
	{
		return (execute_command(shell, node->cmd));
	}
	else if (node->token->type == T_PIPE)
	{
		execute_ast(shell, node->left, exit_code);
		exit_code = execute_ast(shell, node->right, exit_code);
	}
	else if (node->token->type == T_OR)
	{
		exit_code = execute_ast(shell, node->left, exit_code);
		if (exit_code != 0)
			exit_code = execute_ast(shell, node->right, exit_code);
	}
	else if (node->token->type == T_AND)
	{
		exit_code = execute_ast(shell, node->left, exit_code);
		if (exit_code == 0)
			exit_code = execute_ast(shell, node->right, exit_code);
	}
	return (exit_code);
}

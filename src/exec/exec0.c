/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:20:20 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/27 16:08:35 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_ast(t_shell *shell, t_tree *node, int exit_code)
{
	if (!node)
		return (1);
	if (node->cmd)
	{
		if (execute_builtin(shell, node->cmd->name) != -1)
			return (execute_builtin(shell, node->cmd));
		else
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

int	execute_builtin(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->name, "export") == 0)
		return (builtin_export(shell, cmd));
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (builtin_unset(&shell->env_list, cmd));
	if (ft_strcmp(cmd->name, "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (builtin_exit(shell, cmd));
	return (1);
}

int	execute_command(t_shell *shell, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	return (0);
}

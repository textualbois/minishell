/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:20:20 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/30 12:32:45 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
int	execute_command(t_shell *shell, t_command *cmd);
int	execute_ast(t_shell *shell, t_tree *node, int exit_code)
{
	(void)shell;
	if (!node)
		return (1);
	if (node->cmd)
	{
		exit_code = execute_command(shell, node->cmd);
	}
	else if (node->token->type == T_PIPE)
	{
		exit_code = pipex_wrapper(shell, node->left->cmd);
	}
	else if (node->token->type == T_OR)
	{
		exit_code = execute_ast(shell, node->left, exit_code);
		if (exit_code != EXIT_SUCCESS)
			exit_code = execute_ast(shell, node->right, exit_code);
	}
	else if (node->token->type == T_AND)
	{
		exit_code = execute_ast(shell, node->left, exit_code);
		if (exit_code == EXIT_SUCCESS)
			exit_code = execute_ast(shell, node->right, exit_code);
	}
	return (exit_code);
}

int	execute_builtin(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (builtin_echo(cmd->args));
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (builtin_cd(shell, cmd->args));
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->name, "export") == 0)
		return (builtin_export(shell, cmd->args));
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (builtin_unset(&shell->env_list, cmd->args[1]));
	if (ft_strcmp(cmd->name, "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (builtin_exit());
	return (1);
}

int	execute_command(t_shell *shell, t_command *cmd)
{
	if (execute_builtin(shell, cmd) == 0)
		return (0);
	return (1);
}

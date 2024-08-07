/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:20:20 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/09 14:03:20 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	create_and_close_files(t_command *cmd);

int	execute_ast(t_shell *shell, t_tree *node, int exit_code)
{
	printf("execute_ast opened\n");
	if (!node->token)
		return (create_and_close_files(node->cmd), 0);
	else if (node->cmd && node->cmd->name)
	{
		if (is_builtin(node->cmd))
			return (execute_builtin(shell, node->cmd));
		exit_code = pipex_wrapper(shell, node->cmd);
	}
	else if (node->token->type == T_PIPE)
		exit_code = pipex_wrapper(shell, node->left->cmd);
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

/*
* @brief: Executes a builtin command if it exists.
*/
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
		return (builtin_exit(shell, cmd));
	return (1);
}

/*
* @brief: Checks if the command is a builtin command.
*/
int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (true);
	return (false);
}

static int	create_and_close_files(t_command *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->output_file)
	{
		if (cmd->append_output)
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Error: Failed to open output file\n");
			return (EXIT_FAILURE);
		}
	}
	if (fd != 0)
		close(fd);
	unlink(cmd->output_file);
	return (EXIT_SUCCESS);
}

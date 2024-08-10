/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:28:48 by isemin            #+#    #+#             */
/*   Updated: 2024/08/10 14:33:41 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
* @brief: Executes a builtin command if it exists.
*/
int	execute_builtin(t_shell *shell, t_command *cmd)
{
	int	exit_code;
	int	fd[4][2];

	printf("doing builtin\n");
	fd[3][READ_END] = dup(STDIN_FILENO); // save the current stdin
	fd[3][WRITE_END] = dup(STDOUT_FILENO); // save the current stdout
	set_fds_pipe4shell(fd, 1, cmd);
	exit_code = EXIT_FAILURE;
	if (ft_strcmp(cmd->name, "echo") == 0)
		exit_code = builtin_echo(cmd->args);
	if (ft_strcmp(cmd->name, "cd") == 0)
		exit_code = builtin_cd(shell, cmd->args);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		exit_code = builtin_pwd();
	if (ft_strcmp(cmd->name, "export") == 0)
		exit_code = builtin_export(shell, cmd->args);
	if (ft_strcmp(cmd->name, "unset") == 0)
		exit_code = builtin_unset(&shell->env_list, cmd->args[1]);
	if (ft_strcmp(cmd->name, "env") == 0)
		exit_code = builtin_env(shell);
	if (ft_strcmp(cmd->name, "exit") == 0)
		exit_code = builtin_exit(shell, cmd);
	close_all_4shell(fd);
	if (dup2(fd[3][READ_END], STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(fd[3][WRITE_END], STDOUT_FILENO) == -1)
		perror("dup2");

	return (exit_code);
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
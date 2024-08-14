/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:28:48 by isemin            #+#    #+#             */
/*   Updated: 2024/08/14 20:27:22 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_builtin_w_pipe(t_shell *shell, t_command *cmd)
{
	int	exit_code;

	exit_code = EXIT_FAILURE;
	if (ft_strcmp(cmd->name, "echo") == 0)
		exit_code = builtin_echo(cmd->args);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		exit_code = builtin_cd(shell, cmd->args);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		exit_code = builtin_pwd();
	else if (ft_strcmp(cmd->name, "export") == 0)
		exit_code = builtin_export(shell, cmd->args);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		exit_code = builtin_unset(shell, cmd->args[1]);
	else if (ft_strcmp(cmd->name, "env") == 0)
		exit_code = builtin_env(shell, cmd->args);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		exit_code = builtin_exit(shell, cmd);
	else
	{
		ft_putstr_fd(cmd->name, 2);
		ft_putstr_fd(" was not recognised", 2);
		ft_putstr_fd("\n", 2);
	}
	return (exit_code);
}

/*
* @brief: Executes a builtin command if it exists.
*/
int	execute_builtin(t_shell *shell, t_command *cmd)
{
	int	exit_code;
	int	fd[4][2];

	init_fds_pipe4shell(fd);
	save_stdio(fd[3]);
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
		exit_code = builtin_unset(shell, cmd->args[1]);
	if (ft_strcmp(cmd->name, "env") == 0)
		exit_code = builtin_env(shell, cmd->args);
	if (ft_strcmp(cmd->name, "exit") == 0)
		exit_code = builtin_exit(shell, cmd);
	close_all_4shell(fd);
	restore_stdio(fd[3]);
	return (exit_code);
}

void	init_fds_pipe4shell(int fd[4][2])
{
	fd[0][0] = -1;
	fd[0][1] = -1;
	fd[1][0] = -1;
	fd[1][1] = -1;
	fd[2][0] = -1;
	fd[2][1] = -1;
	fd[3][0] = -1;
	fd[3][1] = -1;
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

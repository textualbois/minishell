/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:14:48 by isemin            #+#    #+#             */
/*   Updated: 2024/07/27 23:19:23 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipex_wrapper(t_shell *shell, t_command *cmd)
{
	int			exit_code;
	int			fd[3][2];
	int			pid;
	int			i;

	i = 2;
	while (cmd != NULL)
	{
		//pre-route dependiong on infile/outfile/append/here_doc?
		if (set_fds(fd, i - 1, cmd->argc - 2, cmd) != -1)
		{
			pid = fork();
			if (pid < 0)
				werror_exit(EXIT_FAILURE, "fork_failed", 2);
			else if (pid == CHILD)
			{
				close(fd[((i - 1) % 2) + 1][READ_END]);
				try_execution(cmd->name, shell->path, shell->env);
			}
		}

		i++;
	}
	return (exit_code);
}


int	pipex(int argc, char **argv, char **envp) //todo refactor
{
	char	**path;
	int		res_code;

		path = get_path(envp);
		res_code = here_doc(argc, argv, path, envp);
		res_code = execute_args(argc, argv, path, envp);

	return (res_code);
}

int	execute_args(int argc, char **argv, char **env_paths, char **envp)
{
	int	fd[3][2];
	int	pid;
	int	arg_i;

	arg_i = 2;
	while (arg_i < argc - 1)
	{
		if (set_fds(fd, arg_i - 1, argc - 2, argv) != -1)
		{
			pid = fork();
			if (pid < 0)
				werror_exit(EXIT_FAILURE, "fork_failed", 2);
			else if (pid == CHILD)
			{
				close(fd[((arg_i - 1) % 2) + 1][READ_END]);
				try_execution(argv[arg_i], env_paths, envp);
			}
		}
		close_fds_parent(fd, arg_i - 1, argc - 2);
		arg_i++;
	}
	return (parent_await(pid, fd));
}

int	execute_args_h_doc(int argc, char **argv, char **env_paths, char **envp)
{
	int	fd[3][2];
	int	pid;
	int	arg_i;

	arg_i = 2;
	while (arg_i < argc - 1)
	{
		if (set_fds_h_doc(fd, arg_i - 1, argc - 2, argv) != -1)
		{
			pid = fork();
			if (pid < 0)
				werror_exit(EXIT_FAILURE, "fork_failed", 2);
			else if (pid == CHILD)
			{
				close(fd[((arg_i - 1) % 2) + 1][READ_END]);
				try_execution(argv[arg_i], env_paths, envp);
			}
		}
		close_fds_parent(fd, arg_i - 1, argc - 2);
		arg_i++;
	}
	return (parent_await(pid, fd));
}
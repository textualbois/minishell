/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 06:04:46 by isemin            #+#    #+#             */
/*   Updated: 2024/08/08 10:19:10 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	try_execution(char *cmd, char **env_paths, char **envp)
{
	char	**args;
	char	*full_path;

	args = parse_args(cmd);
	full_path = get_full_path(args[0], env_paths);
	if (full_path != NULL)
	{
		if (access(full_path, X_OK) == -1)
			werror_exit(127, ft_strjoin("permission denied: ", cmd), 2);
		if (execve(full_path, args, envp) == -1)
		{
			free(full_path);
			perror("execve failed");
		}
	}
	clear_arr(args);
	exit(EXIT_FAILURE);
}

static int	parent_await(int last_pid, int fd_array[3][2])
{
	int	status;
	int	pid;

	pid = waitpid(last_pid, &status, 0);
	close_all(fd_array);
	close(STDIN_FILENO);
	while (pid != -1)
		pid = wait(NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
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

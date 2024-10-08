/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:14:48 by isemin            #+#    #+#             */
/*   Updated: 2024/08/13 16:22:33 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent_await(int last_pid, int fd_array[4][2]);
static void	try_execution(char *cmd, char **args, char \
							**env_paths, char **envp);

//maybe comment out this
static void	pipe_fd_init(int fd[4][2])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		fd[i][0] = -1;
		fd[i][1] = -1;
		i++;
	}
}

void	child_sequence(int fd[][2], int index, t_command *cmd, t_shell *shell)
{
	signal(SIGQUIT, sigquit_handler);
	close(fd[(index % 2) + 1][READ_END]);
	if (cmd->name == NULL)
		exit(EXIT_SUCCESS);
	else if (is_builtin(cmd))
		exit(execute_builtin(shell, cmd));
	else
		try_execution(cmd->name, cmd->args, shell->path, shell->env);
}

int	pipex_wrapper(t_shell *shell, t_command *cmd)
{
	int			fd[4][2];
	int			pid;
	int			cmd_num;

	pipe_fd_init(fd);
	cmd_num = 1;
	save_stdio(fd[3]);
	while (cmd != NULL)
	{
		if (set_fds_pipe4shell(fd, cmd_num, cmd) != -1)
		{
			pid = fork();
			if (pid < 0)
				werror_exit(EXIT_FAILURE, "fork_failed", 2);
			else if (pid == CHILD)
				child_sequence(fd, cmd_num, cmd, shell);
		}
		close_fds_parent4shell(fd, cmd_num, cmd);
		cmd = cmd->next;
		cmd_num++;
	}
	return (parent_await(pid, fd));
}

static int	parent_await(int last_pid, int fd_array[4][2])
{
	int	status;
	int	pid;

	pid = waitpid(last_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			printf("Quit: %d\n", WTERMSIG(status));
		close_all_4shell(fd_array);
		close(STDIN_FILENO);
		restore_stdio(fd_array[3]);
		return (128 + WTERMSIG(status));
	}
	close_all_4shell(fd_array);
	close(STDIN_FILENO);
	restore_stdio(fd_array[3]);
	while (pid != -1)
		pid = wait(NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static void	try_execution(char *cmd, char **args, char **env_paths, char **envp)
{
	char	*full_path;

	full_path = get_full_path(cmd, env_paths);
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

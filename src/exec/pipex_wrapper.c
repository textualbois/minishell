/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:14:48 by isemin            #+#    #+#             */
/*   Updated: 2024/08/08 19:21:19 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent_await(int last_pid, int fd_array[3][2]);
static void	try_execution(char *cmd, char **args, char **env_paths, char **envp);

//maybe comment out this
static void	pipe_fd_init(int fd[4][2])
{
	int 		i;

	i = 0;
	while (i < 4)
	{
		fd[i][0] = -1;
		fd[i][1] = -1;
		i++;
	}
}

static void	close_all_4shell(int fd_array[4][2])
{
	int	i;

	i = 2;
	while (i >= 0)
	{
		if (fd_array[i][WRITE_END] != -1)
		{
			if (close(fd_array[i][WRITE_END]) == -1)
				perror("close");
		}
		if (fd_array[i][READ_END] != -1)
		{
			if (close(fd_array[i][READ_END]) == -1)
				perror("close");
		}
		i--;
	}
}

int	pipex_wrapper(t_shell *shell, t_command *cmd)
{
	int			fd[4][2];
	int			pid;
	int			i;

	pipe_fd_init(fd);
	i = 2;
	fd[3][READ_END] = dup(STDIN_FILENO); // save the current stdin
	fd[3][WRITE_END] = dup(STDOUT_FILENO); // save the current stdout
	if (fd[3][READ_END] == -1 || fd[3][WRITE_END] == -1)
		return (perror_return(EXIT_FAILURE, "dup error"));
	while (cmd != NULL)
	{
		if (set_fds_pipe4shell(fd, i - 1, cmd) != -1)
		{
			pid = fork();
			if (pid < 0)
				werror_exit(EXIT_FAILURE, "fork_failed", 2);
			else if (pid == CHILD)
			{	
				// if (cmd->next == NULL)
				signal(SIGQUIT, sigquit_handler);
				if (fd[((i - 1) % 2) + 1][READ_END] != -1)
					close(fd[((i - 1) % 2) + 1][READ_END]);
				if (cmd->name == NULL)
					exit(EXIT_SUCCESS);
				else if (is_builtin(cmd))
					exit(execute_builtin(shell, cmd));
				else
					try_execution(cmd->name, cmd->args, shell->path, shell->env);
			}
		}
		close_fds_parent4shell(fd, i - 1, cmd);
		cmd = cmd->next;
		i++;
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
		if (close(STDIN_FILENO) == -1)
			perror("close error");
		if (dup2(fd_array[3][READ_END], STDIN_FILENO) == -1)
			perror("dup2");
		if (dup2(fd_array[3][WRITE_END], STDOUT_FILENO) == -1)
			perror("dup2");
		return (128 + WTERMSIG(status));
	}
	close_all_4shell(fd_array);
	if (close(STDIN_FILENO) == -1)
		perror("close error");
	if (dup2(fd_array[3][READ_END], STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(fd_array[3][WRITE_END], STDOUT_FILENO) == -1)
		perror("dup2");
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

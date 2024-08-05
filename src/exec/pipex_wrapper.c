/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:14:48 by isemin            #+#    #+#             */
/*   Updated: 2024/08/03 20:30:58 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent_await(int last_pid, int fd_array[3][2]);
static void	try_execution(char *cmd, char **args, char **env_paths, char **envp);

//maybe comment out this
static void pipe_fd_init(int fd[4][2])
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
			// ft_putstr_fd("closing fd_array[", 2);
			// ft_putnbr_fd(i, 2);
			// ft_putstr_fd("][WRITE_END]\n", 2);
			if (close(fd_array[i][WRITE_END]) == -1)
				perror("close");
		}
		if (fd_array[i][READ_END] != -1)
		{
			// ft_putstr_fd("closing fd_array[", 2);
			// ft_putnbr_fd(i, 2);
			// ft_putstr_fd("][READ_END]\n", 2);
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
	// t_command *temp = cmd;

	// while(temp)
	// {
	// 	printf("cmd->name: %s\n", temp->name);
	// 	temp = temp->next;
	// }
	// printf("pipex_wrapper\n");
	// printf("cmd->name: %s\n", cmd->name);
	pipe_fd_init(fd);
	i = 2;
	fd[3][READ_END] = dup(STDIN_FILENO); // save the current stdin
	fd[3][WRITE_END] = dup(STDOUT_FILENO); // save the current stdout
	// ft_putstr_fd("saving stdin and stdout for later\n", 2);
	if (fd[3][READ_END] == -1 || fd[3][WRITE_END] == -1)
		return (perror_return(EXIT_FAILURE, "dup error"));
	// fflush(stdout);
	while (cmd != NULL)
	{
		if (set_fds_pipe4shell(fd, i - 1, cmd) != -1)
		{
			//add builtin check here. if builtin, maybe fork is unnecessary
			pid = fork();
			if (pid < 0)
				werror_exit(EXIT_FAILURE, "fork_failed", 2);
			else if (pid == CHILD)
			{
				if (fd[((i - 1) % 2) + 1][READ_END] != -1)
				{
					close(fd[((i - 1) % 2) + 1][READ_END]); // do we close correctly?
					// ft_putstr_fd("IN_CHILD closing fd[", 2);
					// ft_putnbr_fd(((i - 1) % 2) + 1, 2);
					// ft_putstr_fd("][READ_END]\n", 2);
				}
				if (cmd->name == NULL)
				{
					// ft_putstr_fd("no command name - ", 2);
					// ft_putstr_fd("which means no command\n", 2);
					exit(EXIT_SUCCESS);
				}
				else if (is_builtin(cmd))
					exit(execute_builtin(shell, cmd));
				else
					try_execution(cmd->name, cmd->args, shell->path, shell->env);
			}
		}
		close_fds_parent4shell(fd, i - 1, cmd);
		cmd = cmd->next;
		// ft_putstr_fd("cmd #" , 2);
		// ft_putnbr_fd(i - 1, 2);
		// ft_putstr_fd(" done\n", 2);
		i++;
	}
	return (parent_await(pid, fd));
}

static int	parent_await(int last_pid, int fd_array[4][2])
{
	int	status;
	int	pid;

	pid = waitpid(last_pid, &status, 0);
	close_all_4shell(fd_array);
	// ft_putstr_fd("closing STDIN_FILENO specifically\n", 2);
	if (close(STDIN_FILENO) == -1)
		perror("close error");
	// ft_putstr_fd("duping back to original stdIN\n", 2);
	if (dup2(fd_array[3][READ_END], STDIN_FILENO) == -1) // restore the original stdin
		perror("dup2");
	// ft_putstr_fd("duping back to original stdOUT\n", 2);
	if (dup2(fd_array[3][WRITE_END], STDOUT_FILENO) == -1) // restore the original stdout
		perror("dup2");
	while (pid != -1)
		pid = wait(NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static void	try_execution(char *cmd, char **args, char **env_paths, char **envp)
{
	//char	**args;
	char	*full_path;

	//args = parse_args(cmd);
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

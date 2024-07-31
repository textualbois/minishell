/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:14:48 by isemin            #+#    #+#             */
/*   Updated: 2024/07/31 15:39:03 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent_await(int last_pid, int fd_array[3][2]);
static void	try_execution(char *cmd, char **args, char **env_paths, char **envp);


// one question - is the fd of an open file handled correctly \
// when the next command also has it's own input file and would take over the fd slot?

int	pipex_wrapper(t_shell *shell, t_command *cmd)
{
	int			fd[4][2];
	int			pid;
	int			i;
	t_command *temp = cmd;

	// while(temp)
	// {
	// 	printf("cmd->name: %s\n", temp->name);
	// 	temp = temp->next;
	// }
	// printf("pipex_wrapper\n");
	// printf("cmd->name: %s\n", cmd->name);
	i = 2;
	fd[3][READ_END] = dup(STDIN_FILENO); // save the current stdin
	fd[3][WRITE_END] = dup(STDOUT_FILENO); // save the current stdout
	if (fd[3][READ_END] == -1 || fd[3][WRITE_END] == -1)
		return (perror_return(EXIT_FAILURE, "dup error"));
	while (cmd != NULL)
	{
		// ft_putstr_fd("cmd #", 2);
		// ft_putnbr_fd(i - 1, 2);
		// ft_putstr_fd("\n", 2);
		//pre-route dependiong on infile/outfile/append/here_doc?
		if (set_fds_pipe4shell(fd, i - 1, cmd) != -1)
		{
			//add builtin check here. if builtin, maybe fork is unnecessary
			pid = fork();
			if (pid < 0)
				werror_exit(EXIT_FAILURE, "fork_failed", 2);
			else if (pid == CHILD)
			{
				close(fd[((i - 1) % 2) + 1][READ_END]); // do we close correctly?
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

static int	parent_await(int last_pid, int fd_array[3][2])
{
	int	status;
	int	pid;

	pid = waitpid(last_pid, &status, 0);
	close_all(fd_array);
	// ft_putstr_fd("closing STDIN_FILENO specifically\n", 2);
	close(STDIN_FILENO);
	// ft_putstr_fd("duping back to original stdin and stdout\n", 2);
	dup2(fd_array[3][READ_END], STDIN_FILENO); // restore the original stdin
	dup2(fd_array[3][WRITE_END], STDOUT_FILENO); // restore the original stdout
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

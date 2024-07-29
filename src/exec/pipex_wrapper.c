/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wrapper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:14:48 by isemin            #+#    #+#             */
/*   Updated: 2024/07/30 00:07:19 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	parent_await(int last_pid, int fd_array[3][2]);
static void	try_execution(char *cmd, char **args, char **env_paths, char **envp);


// one question - is the fd of an open file handled correctly \
// when the next command also has it's own input file and would take over the fd slot?

int	pipex_wrapper(t_shell *shell, t_command *cmd)
{
	int			fd[3][2];
	int			pid;
	int			i;

	i = 2;
	while (cmd != NULL)
	{
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
				try_execution(cmd->name, cmd->args, shell->path, shell->env);
			}
		}
		close_fds_parent4shell(fd, i, cmd);
		i++;
		cmd = cmd->next;
	}
	return (parent_await(pid, fd));
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

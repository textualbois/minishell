/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:59:57 by isemin            #+#    #+#             */
/*   Updated: 2024/07/30 00:15:31 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	set_ins(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (cmd->heredoc_delimiter != NULL) //todo if we have a heredoc to handle
	{
		here_doc4shell(fd_array, cmd, cmd->heredoc_delimiter); // take user input, put it into fd[0][READ_END]
		if (dup2(fd_array[0][READ_END], STDIN_FILENO) == -1)
			return (perror_return(EXIT_FAILURE, "1_dup2"));
	}
	else if (cmd->input_file != NULL) //todo if we have input file to handle
	{
		if (setup_infile_read_fd(fd_array, cmd->input_file) != 0)
			return (EXIT_FAILURE);
	}
	else // if we have a pipe or no file // possible handle differently when the command is the first one
	{
		if (redirect_input_between_pipes(fd_array, cmd_num) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	set_outs(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (cmd->append_output) //todo if we have append output file to handle
	{
		if (setup_append_outfile(fd_array, cmd->output_file) != 0)
			return (EXIT_FAILURE);
	}
	else if (cmd->output_file) //todo if we have output file to handle
	{
		if (setup_outfile(fd_array, cmd->output_file) != 0)
			return (EXIT_FAILURE);
	}
	else // if we have a pipe or no file // possible handle differently when the command is the last one
	{
		if (redirect_out_between_pipes(fd_array, cmd_num, cmd) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	set_fds_pipe4shell(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (pipe(fd_array[(cmd_num % 2) + 1]) == -1)
		return (perror_return(EXIT_FAILURE, "pipe error"));
	if (set_ins(fd_array, cmd_num, cmd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (set_outs(fd_array, cmd_num, cmd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	close_fds_parent4shell(int fd_array[][2], int cmd_num, t_command *cmd)
{
	(void)cmd;
	if (cmd->heredoc_delimiter != NULL)
		close(fd_array[0][WRITE_END]);
	else if (cmd->output_file != NULL)
		close(fd_array[0][WRITE_END]);
	else
		close(fd_array[(cmd_num % 2) + 1][WRITE_END]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:59:57 by isemin            #+#    #+#             */
/*   Updated: 2024/08/13 16:30:12 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	set_ins(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (cmd->heredoc_delimiter != NULL)
	{
		here_doc4shell(fd_array, cmd, cmd->heredoc_delimiter);
		if (dup2(fd_array[0][READ_END], STDIN_FILENO) == -1)
			return (perror_return(EXIT_FAILURE, "dup2"));
		else
			close(fd_array[0][READ_END]);
	}
	else if (cmd->input_file != NULL)
	{
		if (setup_infile_read_fd(fd_array, cmd->input_file) != 0)
			return (EXIT_FAILURE);
	}
	else
	{
		if (redirect_input_between_pipes(fd_array, cmd_num) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	set_outs(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (cmd->append_output)
	{
		if (setup_append_outfile(fd_array, cmd->output_file) != 0)
			return (EXIT_FAILURE);
	}
	else if (cmd->output_file)
	{
		if (setup_outfile(fd_array, cmd->output_file) != 0)
			return (EXIT_FAILURE);
	}
	else
	{
		if (redirect_out_between_pipes(fd_array, cmd_num, cmd) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	set_fds_pipe4shell(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (cmd->next != NULL)
	{
		if (pipe(fd_array[(cmd_num % 2) + 1]) == -1)
			return (perror_return(EXIT_FAILURE, "pipe error"));
	}
	if (set_ins(fd_array, cmd_num, cmd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (set_outs(fd_array, cmd_num, cmd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	close_fds_parent4shell(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (cmd->heredoc_delimiter != NULL)
	{
		if (close(fd_array[0][WRITE_END]) == -1)
			close(fd_array[0][WRITE_END]);
	}
	else if (cmd->output_file != NULL)
	{
		if (fd_array[0][WRITE_END] != -1)
			close(fd_array[0][WRITE_END]);
	}
	else
	{
		if (fd_array[(cmd_num % 2) + 1][WRITE_END] != -1)
			close(fd_array[(cmd_num % 2) + 1][WRITE_END]);
	}
}

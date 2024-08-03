/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:59:57 by isemin            #+#    #+#             */
/*   Updated: 2024/08/03 20:25:39 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	set_ins(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (cmd->heredoc_delimiter != NULL) // if we have heredoc
	{
		here_doc4shell(fd_array, cmd, cmd->heredoc_delimiter); // take user input, put it into fd[0][READ_END]
		if (dup2(fd_array[0][READ_END], STDIN_FILENO) == -1)
			return (perror_return(EXIT_FAILURE, "1_dup2"));
		// else
		// {
		// 	ft_putstr_fd("redirected stdin to heredoc\n", 2);
		// }
	}
	else if (cmd->input_file != NULL) //todo if we have input file to handle
	{
		if (setup_infile_read_fd(fd_array, cmd->input_file) != 0) //B
			return (EXIT_FAILURE);
	}
	else // if we have a pipe or no file // possible handle differently when the command is the first one
	{
		if (redirect_input_between_pipes(fd_array, cmd_num) != 0) //C
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	set_outs(int fd_array[][2], int cmd_num, t_command *cmd)//F
{
	if (cmd->append_output) // if we have append output file to handle //F.2.2.append
	{
		// ft_putstr_fd("append output file: ", 2);
		// ft_putstr_fd(cmd->output_file, 2);
		// ft_putstr_fd("\n", 2);
		if (setup_append_outfile(fd_array, cmd->output_file) != 0)
			return (EXIT_FAILURE);
	}
	else if (cmd->output_file) // if we have output file to handle //F.2.2.overwrite
	{
		if (setup_outfile(fd_array, cmd->output_file) != 0)
			return (EXIT_FAILURE);
	}
	else // if we have a pipe or no file // possible handle differently when the command is the last one
	{
		if (redirect_out_between_pipes(fd_array, cmd_num, cmd) != 0) //F.2.1
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	set_fds_pipe4shell(int fd_array[][2], int cmd_num, t_command *cmd)
{

	if (cmd_num != 1 || cmd->next != NULL)
	{
		if (pipe(fd_array[(cmd_num % 2) + 1]) == -1) //A creates a pipe at this location. no commitment to use it
			return (perror_return(EXIT_FAILURE, "pipe error"));
		// else
		// {
		// 	ft_putstr_fd("pipe created for cmd number ", 2);
		// 	ft_putnbr_fd(cmd_num, 2);
		// 	ft_putstr_fd(" at pipe index ", 2);
		// 	ft_putnbr_fd((cmd_num % 2) + 1, 2);
		// 	ft_putstr_fd("\n", 2);
		// }
	}
	// else
	// {
	// 	ft_putstr_fd("no pipe created for cmd number ", 2);
	// 	ft_putnbr_fd(cmd_num, 2);
	// 	ft_putstr_fd("\n", 2);
	// }
	if (set_ins(fd_array, cmd_num, cmd) != EXIT_SUCCESS) //B and C
		return (EXIT_FAILURE);
	if (set_outs(fd_array, cmd_num, cmd) != EXIT_SUCCESS) //F
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	close_fds_parent4shell(int fd_array[][2], int cmd_num, t_command *cmd)
{
	// ft_putstr_fd("IN PARENT ", 2);
	// ft_putstr_fd("closing STDOUT_FILENO\n", 2);
	// if (close(STDOUT_FILENO) == -1)
	// 	perror("close");
	if (cmd->heredoc_delimiter != NULL)
	{
		// ft_putstr_fd("closing fd[", 2);
		// ft_putnbr_fd(0, 2);
		// ft_putstr_fd("][WRITE_END]\n", 2);
		if (close(fd_array[0][WRITE_END]) == -1)
			perror("close");
	}
	else if (cmd->output_file != NULL)
	{
		// ft_putstr_fd("closing fd[", 2);
		// ft_putnbr_fd(0, 2);
		// ft_putstr_fd("][WRITE_END]\n", 2);
		if (close(fd_array[0][WRITE_END]) == -1)
			perror("close");
	}
	else
	{
		if (fd_array[(cmd_num % 2) + 1][WRITE_END] != -1)
		{
			// ft_putstr_fd("closing fd[", 2);
			// ft_putnbr_fd((cmd_num % 2) + 1, 2);
			// ft_putstr_fd("][WRITE_END]\n", 2);
			if (close(fd_array[(cmd_num % 2) + 1][WRITE_END]) == -1)
				perror("close");
		}
	}
}

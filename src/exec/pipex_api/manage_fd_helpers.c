/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:27:40 by isemin            #+#    #+#             */
/*   Updated: 2024/08/07 16:12:11 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	setup_infile_read_fd(int fd_array[][2], char *input_file) //B.2 completely copies from pipex
{
	fd_array[0][READ_END] = open(input_file, O_RDONLY);
	if (fd_array[0][READ_END] == -1)
		return (perror_return(EXIT_FAILURE, input_file));
	if (dup2(fd_array[0][READ_END], STDIN_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, "1_dup2"));
	else
		close(fd_array[0][READ_END]);
	// {
	// 	ft_putstr_fd("redirected stdin to input_file\n", 2);
	// 	//close(fd_array[0][READ_END]);
	// }
	return (EXIT_SUCCESS);
}

int	setup_outfile(int fd_array[][2], char *output_file)
{
	fd_array[0][WRITE_END] = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_array[0][WRITE_END] == -1)
		return (perror_return(EXIT_FAILURE, output_file));
	if (dup2(fd_array[0][WRITE_END], STDOUT_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, output_file));
	else
		close(fd_array[0][WRITE_END]);
	// {
	// 	ft_putstr_fd("redirected stdout to output_file\n", 2);
	// 	//close(fd_array[0][WRITE_END]);
	// }
	return (EXIT_SUCCESS);
}

int	setup_append_outfile(int fd_array[][2], char *output_file)
{
	fd_array[0][WRITE_END] = open(output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd_array[0][WRITE_END] == -1)
		return (perror_return(EXIT_FAILURE, output_file));
	if (dup2(fd_array[0][WRITE_END], STDOUT_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, output_file));
	else
		close(fd_array[0][WRITE_END]);
	// {
	// 	ft_putstr_fd("redirected stdout to output_file (appendable)\n", 2);
	// 	//close(fd_array[0][WRITE_END]);
	// }
	return (EXIT_SUCCESS);
}

// it errors in dup2 because the file descriptor is not valid
//the file descriptor is not valid, because we didn't initialize it?

int	redirect_input_between_pipes(int fd_array[][2], int cmd_num) //C.2 only difference is we don't redirect for first command
{
	if (cmd_num == 1) // if we are at the first command do nothing (because we take input from stdin)
	{
		// ft_putstr_fd("no redirection needed for first command\n", 2);
		// dup2(fd_array[3][READ_END], STDIN_FILENO); // restore the original stdin
		// close(fd_array[3][READ_END]);
		return (EXIT_SUCCESS);
	}
	if (dup2(fd_array[2 - (cmd_num % 2)][READ_END], STDIN_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, "dup2 input error"));
	else
		close(fd_array[2 - (cmd_num % 2)][READ_END]);
	// {
	// 	ft_putstr_fd("redirected stdin to pipe at pip index ", 2);
	// 	ft_putnbr_fd(2 - (cmd_num % 2), 2);
	// 	ft_putstr_fd("[READ_END]\n", 2);
	// }
	return (EXIT_SUCCESS);
}

int	redirect_out_between_pipes(int fd_array[][2], int cmd_num, t_command *cmd) //F.2.1
{
	if (cmd->next == NULL) //if we are at the last command, don't redirect
	{
		// ft_putstr_fd("restoring stdout location for last command\n", 2);
		dup2(fd_array[3][WRITE_END], STDOUT_FILENO); // restore the original stdout
		close(fd_array[3][WRITE_END]);
		//dup2(STDOUT_FILENO, fd_array[3][WRITE_END]); // restore the original stdout
		return (EXIT_SUCCESS);
	}
	// ft_putstr_fd("trying to redirect stdout to pipe at pipe index ", 2);
	// ft_putnbr_fd((cmd_num % 2) + 1, 2);
	// ft_putstr_fd("[WRITE_END]\n", 2);
	if (dup2(fd_array[(cmd_num % 2) + 1][WRITE_END], STDOUT_FILENO) == -1)
			return (perror_return(EXIT_FAILURE, "2_dup2"));
	else
		close(fd_array[(cmd_num % 2) + 1][WRITE_END]);
	// {
	// 	ft_putstr_fd("redirected stdout to pipe at pipe index ", 2);
	// 	ft_putnbr_fd((cmd_num % 2) + 1, 2);
	// 	ft_putstr_fd("[WRITE_END]\n", 2);
	// }
	return (EXIT_SUCCESS);
}

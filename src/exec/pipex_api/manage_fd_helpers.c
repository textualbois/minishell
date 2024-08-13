/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 20:27:40 by isemin            #+#    #+#             */
/*   Updated: 2024/08/13 16:28:29 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	setup_infile_read_fd(int fd_array[][2], char *input_file)
{
	fd_array[0][READ_END] = open(input_file, O_RDONLY);
	if (fd_array[0][READ_END] == -1)
		return (perror_return(EXIT_FAILURE, input_file));
	if (dup2(fd_array[0][READ_END], STDIN_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, "dup2"));
	else if (fd_array[0][READ_END] != -1)
		close(fd_array[0][READ_END]);
	return (EXIT_SUCCESS);
}

int	setup_outfile(int fd_array[][2], char *output_file)
{
	fd_array[0][WRITE_END] = open(output_file, O_WRONLY
			| O_TRUNC | O_CREAT, 0644);
	if (fd_array[0][WRITE_END] == -1)
		return (perror_return(EXIT_FAILURE, output_file));
	if (dup2(fd_array[0][WRITE_END], STDOUT_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, output_file));
	else if (fd_array[0][WRITE_END] != -1)
		close(fd_array[0][WRITE_END]);
	return (EXIT_SUCCESS);
}

int	setup_append_outfile(int fd_array[][2], char *output_file)
{
	fd_array[0][WRITE_END] = open(output_file, O_WRONLY
			| O_APPEND | O_CREAT, 0644);
	if (fd_array[0][WRITE_END] == -1)
		return (perror_return(EXIT_FAILURE, output_file));
	if (dup2(fd_array[0][WRITE_END], STDOUT_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, output_file));
	else if (fd_array[0][WRITE_END] != -1)
		close(fd_array[0][WRITE_END]);
	return (EXIT_SUCCESS);
}

// it errors in dup2 because the file descriptor is not valid
//the file descriptor is not valid, because we didn't initialize it?
int	redirect_input_between_pipes(int fd_array[][2], int cmd_num)
{
	if (cmd_num == 1)
	{
		return (EXIT_SUCCESS);
	}
	if (dup2(fd_array[2 - (cmd_num % 2)][READ_END], STDIN_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, "dup2 input error"));
	else if (fd_array[2 - (cmd_num % 2)][READ_END] != -1)
		close(fd_array[2 - (cmd_num % 2)][READ_END]);
	return (EXIT_SUCCESS);
}

int	redirect_out_between_pipes(int fd_array[][2], int cmd_num, t_command *cmd)
{
	if (cmd->next == NULL)
	{
		dup2(fd_array[3][WRITE_END], STDOUT_FILENO);
		close(fd_array[3][WRITE_END]);
		return (EXIT_SUCCESS);
	}
	if (dup2(fd_array[(cmd_num % 2) + 1][WRITE_END], STDOUT_FILENO) == -1)
		return (perror_return(EXIT_FAILURE, "2_dup2"));
	else if (fd_array[(cmd_num % 2) + 1][WRITE_END] != -1)
		close(fd_array[(cmd_num % 2) + 1][WRITE_END]);
	return (EXIT_SUCCESS);
}

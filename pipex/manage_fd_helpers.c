/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:14:37 by isemin            #+#    #+#             */
/*   Updated: 2024/05/01 15:25:51 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	setup_initial_read_fd(int fd_array[][2], char **argv)
{
	fd_array[0][READ_END] = open(argv[1], O_RDONLY);
	if (fd_array[0][READ_END] == -1)
		return (perror_return(-1, argv[1]));
	if (dup2(fd_array[0][READ_END], STDIN_FILENO) == -1)
		return (perror_return(-1, "dup2"));
	return (0);
}

int	redirect_input(int fd_array[][2], int cmd_num)
{
	if (dup2(fd_array[2 - (cmd_num % 2)][READ_END], STDIN_FILENO) == -1)
		return (perror_return(-1, "dup2 input error"));
	return (0);
}

int	redirect_out(int fd_array[][2], int cmd_num, int cmd_num_lim, char **argv)
{
	if (cmd_num + 1 < cmd_num_lim)
	{
		if (dup2(fd_array[(cmd_num % 2) + 1][WRITE_END], STDOUT_FILENO) == -1)
			return (perror_return(-1, "dup2"));
	}
	else
	{
		fd_array[0][WRITE_END] = open(argv[cmd_num_lim + 1], \
									O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd_array[0][WRITE_END] == -1)
			return (perror_return(-1, argv[cmd_num_lim + 1]));
		if (dup2(fd_array[0][WRITE_END], STDOUT_FILENO) == -1)
			return (perror_return(-1, argv[cmd_num_lim + 1]));
	}
	return (0);
}

int	redirect_out_h_doc(int fd_array[][2], int cmd_num, \
						int cmd_num_lim, char **argv)
{
	if (cmd_num + 1 < cmd_num_lim)
	{
		if (dup2(fd_array[(cmd_num % 2) + 1][WRITE_END], STDOUT_FILENO) == -1)
			return (perror_return(-1, "dup2"));
	}
	else
	{
		fd_array[0][WRITE_END] = open(argv[cmd_num_lim + 1], \
									O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd_array[0][WRITE_END] == -1)
			return (perror_return(-1, argv[cmd_num_lim + 1]));
		if (dup2(fd_array[0][WRITE_END], STDOUT_FILENO) == -1)
			return (perror_return(-1, argv[cmd_num_lim + 1]));
	}
	return (0);
}

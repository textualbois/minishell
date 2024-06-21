/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 00:22:35 by isemin            #+#    #+#             */
/*   Updated: 2024/04/29 03:21:31 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	set_fds(int fd_array[3][2], int cmd_num, int cmd_num_lim, char **argv)
{
	if (pipe(fd_array[(cmd_num % 2) + 1]) == -1)
		return (perror_return(-1, "pipe error"));
	if (cmd_num == 1)
	{
		if (setup_initial_read_fd(fd_array, argv) != 0)
			return (-1);
	}
	else
	{
		if (redirect_input(fd_array, cmd_num) != 0)
			return (-1);
	}
	if (redirect_out(fd_array, cmd_num, cmd_num_lim, argv) != 0)
		return (-1);
	return (1);
}

int	set_fds_h_doc(int fd_array[3][2], int cmd_num, int cmd_num_lim, char **argv)
{
	if (pipe(fd_array[(cmd_num % 2) + 1]) == -1)
		return (perror_return(-1, "pipe error"));
	if (cmd_num == 1)
	{
		if (setup_initial_read_fd(fd_array, argv) != 0)
			return (-1);
	}
	else
	{
		if (redirect_input(fd_array, cmd_num) != 0)
			return (-1);
	}
	if (redirect_out_h_doc(fd_array, cmd_num, cmd_num_lim, argv) != 0)
		return (-1);
	return (1);
}

void	close_fds_parent(int fd_array[3][2], int cmd_num, int cmd_num_lim)
{
	if (cmd_num + 1 < cmd_num_lim)
		close(fd_array[(cmd_num % 2) + 1][WRITE_END]);
	else
		close(fd_array[0][WRITE_END]);
}

void	close_all(int fd_array[3][2])
{
	int	i;

	i = 2;
	while (i >= 0)
	{
		close(fd_array[i][WRITE_END]);
		close(fd_array[i][READ_END]);
		i--;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:59:57 by isemin            #+#    #+#             */
/*   Updated: 2024/07/27 23:19:14 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	set_fds_pipe4shell(int fd_array[3][2], int cmd_num, t_command *cmd)
{
	if (pipe(fd_array[(cmd_num % 2) + 1]) == -1)
		return (perror_return(-1, "pipe error"));
	if (cmd->heredoc_delimiter != NULL) //todo if we have a heredoc to handle
	{
		if (setup_initial_read_fd(fd_array, argv) != 0)
			return (-1);
	}
	else if (cmd->input_file != NULL) //todo if we have input file to handle
	{

	}
	else // if we have a pipe or no file // possible handle differently when the command is the first one
	{
		if (redirect_input(fd_array, cmd_num) != 0)
			return (-1);
	}
	{
		if (redirect_input(fd_array, cmd_num) != 0)
			return (-1);
	}
	if (redirect_out(fd_array, cmd_num, cmd_num_lim, argv) != 0)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_save_restore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:42:08 by isemin            #+#    #+#             */
/*   Updated: 2024/08/13 16:18:28 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	save_stdio(int fd[2])
{
	fd[READ_END] = dup(STDIN_FILENO);
	fd[WRITE_END] = dup(STDOUT_FILENO);
}

void	restore_stdio(int fd[2])
{
	dup2(fd[READ_END], STDIN_FILENO);
	dup2(fd[WRITE_END], STDOUT_FILENO);
}

void	close_all_4shell(int fd_array[4][2])
{
	int	i;

	i = 2;
	while (i >= 0)
	{
		if (fd_array[i][WRITE_END] != -1)
			close(fd_array[i][WRITE_END]);
		if (fd_array[i][READ_END] != -1)
			close(fd_array[i][READ_END]);
		i--;
	}
}

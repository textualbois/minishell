/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_save_restore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:42:08 by isemin            #+#    #+#             */
/*   Updated: 2024/08/12 12:51:23 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	save_stdio(int fd[2])
{
	fd[READ_END] = dup(STDIN_FILENO);
	fd[WRITE_END] = dup(STDOUT_FILENO);
	if (fd[0] == -1 || fd[1] == -1)
		perror("dup");
}

void	restore_stdio(int fd[2])
{
	if (dup2(fd[READ_END], STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		perror("dup2");
}

void	close_all_4shell(int fd_array[4][2])
{
	int	i;

	i = 2;
	while (i >= 0)
	{
		if (fd_array[i][WRITE_END] != -1)
		{
			if (close(fd_array[i][WRITE_END]) == -1)
				perror("close");
		}
		if (fd_array[i][READ_END] != -1)
		{
			if (close(fd_array[i][READ_END]) == -1)
				perror("close");
		}
		i--;
	}
}



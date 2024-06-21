/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:12:09 by isemin            #+#    #+#             */
/*   Updated: 2024/04/28 19:13:13 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(int exit_code, char *error_message)
{
	char	*full_message;

	full_message = ft_strjoin("pipex: ", error_message);
	if (full_message != NULL)
	{
		perror(full_message);
		free(full_message);
	}
	else
		perror(error_message);
	exit(exit_code);
}

int	perror_return(int return_value, char *error_message)
{
	char	*full_message;

	full_message = ft_strjoin("pipex: ", error_message);
	if (full_message != NULL)
	{
		perror(full_message);
		free(full_message);
	}
	else
		perror(error_message);
	return (return_value);
}

void	werror_exit(int exit_code, char *error_message, int fd)
{
	char	*full_message;

	full_message = ft_strjoin("pipex: ", error_message);
	if (full_message != NULL)
	{
		write(fd, full_message, ft_strlen(full_message));
		write(fd, "\n", 1);
		free(full_message);
	}
	else
	{
		write(fd, error_message, ft_strlen(error_message));
		write(fd, "\n", 1);
	}
	exit(exit_code);
}

int	werror_return(int return_value, char *error_message, int fd)
{
	char	*full_message;

	full_message = ft_strjoin("pipex: ", error_message);
	if (full_message != NULL)
	{
		write(fd, full_message, ft_strlen(full_message));
		write(fd, "\n", 1);
		free(full_message);
	}
	else
	{
		write(fd, error_message, ft_strlen(error_message));
		write(fd, "\n", 1);
	}
	return (return_value);
}

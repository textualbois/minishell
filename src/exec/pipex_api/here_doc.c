/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:27:13 by isemin            #+#    #+#             */
/*   Updated: 2024/08/12 14:15:59 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*create_here_doc(void)
{
	char	*here_doc_file;
	char	*base_file_name;
	int		extension_code;
	char	*extension;

	extension_code = 0;
	extension = ft_itoa(extension_code);
	base_file_name = ".here_doc_temp_";
	here_doc_file = ft_strjoin(base_file_name, extension);
	free(extension);
	while (access(here_doc_file, F_OK) == 0)
	{
		free(here_doc_file);
		extension_code++;
		extension = ft_itoa(extension_code);
		here_doc_file = ft_strjoin(base_file_name, extension);
		free(extension);
	}
	return (here_doc_file);
}

static void	receive_input(int file_fd, char *limit)
{
	char	*temp_line;

	while (1)
	{
		temp_line = get_next_line(0, 0);
		if (temp_line == NULL)
			break ;
		else if (ft_strncmp(temp_line, limit, ft_strlen(limit)) == 0 \
				&& ft_strlen(temp_line) == ft_strlen(limit) + \
				(temp_line[ft_strlen(temp_line) - 1] == '\n'))
		{
			free(temp_line);
			break ;
		}
		write(file_fd, temp_line, ft_strlen(temp_line));
		free(temp_line);
	}
}

int	here_doc4shell(int fd_array[][2], t_command *cmd, char *delimiter)
{
	char	*here_doc_file;

	(void)(cmd);
	here_doc_file = create_here_doc();
	fd_array[0][READ_END] = open(here_doc_file,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_array[0][READ_END] == -1)
	{
		perror(here_doc_file);
		free(here_doc_file);
		return (EXIT_FAILURE);
	}
	receive_input(fd_array[0][READ_END], delimiter);
	unlink(here_doc_file);
	free(here_doc_file);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:14:14 by isemin            #+#    #+#             */
/*   Updated: 2024/07/01 15:37:08 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**shift_argv(int argc, char **argv, char *new_infile)
{
	char	**new_argv;
	int		i;
	int		new_size;

	i = 2;
	new_size = argc - 1;
	new_argv = malloc((sizeof(char *) * new_size));
	if (new_argv == NULL)
	{
		perror("Malloc error");
		return (NULL);
	}
	new_argv[0] = argv[0];
	new_argv[1] = new_infile;
	while (i < new_size)
	{
		new_argv[i] = argv[i + 1];
		i++;
	}
	return (new_argv);
}

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

int	here_doc(int argc, char **argv, char **env_paths, char **envp)
{
	char	*here_doc_file;
	int		here_doc_fd;
	char	**new_argv;
	int		status;

	here_doc_file = create_here_doc();
	here_doc_fd = open(here_doc_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (here_doc_fd == -1)
	{
		perror(here_doc_file);
		free(here_doc_file);
		return (EXIT_FAILURE);
	}
	receive_input(here_doc_fd, argv[2]);
	close(here_doc_fd);
	new_argv = shift_argv(argc, argv, here_doc_file);
	if (new_argv != NULL)
		status = execute_args_h_doc(argc - 1, new_argv, env_paths, envp);
	unlink(here_doc_file);
	free(here_doc_file);
	if (new_argv == NULL)
		return (EXIT_FAILURE);
	free(new_argv);
	return (status);
}

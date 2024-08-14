/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:23:19 by isemin            #+#    #+#             */
/*   Updated: 2024/08/15 00:31:38 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path_arr(char *env_path_str)
{
	char	**path_arr_temp;
	char	**path_arr;

	path_arr = NULL;
	path_arr_temp = ft_split(env_path_str + 5, ':');
	if (path_arr_temp != NULL)
	{
		path_arr = ft_map_s2a(path_arr_temp, "/\0", ft_strjoin);
		clear_arr(path_arr_temp);
	}
	return (path_arr);
}

char	*get_full_path(char *cmd, char **env_paths)
{
	char	*full_path;
	int		path_i;

	path_i = 0;
	if (env_paths != NULL)
	{
		while (env_paths[path_i] != NULL)
		{
			full_path = ft_strjoin(env_paths[path_i], cmd);
			if (full_path != NULL && access(full_path, F_OK) != -1)
			{
				clear_arr(env_paths);
				return (full_path);
			}
			free(full_path);
			path_i++;
		}
		clear_arr(env_paths);
	}
	if (ft_strchr(cmd, '/') != NULL && access(cmd, F_OK) != -1)
		return (cmd);
	werror_exit(127, ft_strjoin(cmd, ": command not found"), 2);
	return (NULL);
}

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (get_path_arr(envp[i]));
		i++;
	}
	return (NULL);
}

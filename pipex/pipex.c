/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 04:04:00 by isemin            #+#    #+#             */
/*   Updated: 2024/05/01 15:29:13 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	int		res_code;

	if (argc < 5)
		return (werror_return(EXIT_FAILURE, "too few args", 2));
	if (ft_strlen(argv[1]) == 8 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			return (werror_return(EXIT_FAILURE, "too few args", 2));
		else
		{
			path = get_path(envp);
			res_code = here_doc(argc, argv, path, envp);
		}
	}
	else
	{
		path = get_path(envp);
		res_code = execute_args(argc, argv, path, envp);
	}
	if (path != NULL)
		clear_arr(path);
	return (res_code);
}

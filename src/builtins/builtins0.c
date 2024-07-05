/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:30:36 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/05 16:08:58 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_pwd(t_data *data)
{
	char	**env;

	env = data->env;
	while (*env)
	{
		if (ft_strncmp(*env, "PWD=", 4) == 0)
			return (*env + 4);
		env++;
	}
	return (NULL);
}

int	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = get_env_pwd(data);
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
		ft_putendl_fd("PWD not set in enviroment", STDERR_FILENO);
		return (1);
	}
}

// void ft_env
// {
	
// }

// void ft_echo
// {
	
// }

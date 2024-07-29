/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:30:36 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/29 19:19:59 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief: print arguments, -n no newline.
*/
int	builtin_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n_flag = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 1)
		printf("\n");
	return (0);
}

/*
* @brief: change directory.
*/
int	builtin_cd(t_shell *shell, char **args)
{
	char	*home;

	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		home = get_env_value(shell->env_list, "HOME");
		if (home == NULL)
		{
			perror("cd: HOME not set\n");
			return (1);
		}
		if (chdir(home) != 0)
		{
			perror("cd failed");
			return (1);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		perror("cd failed");
		return (1);
	}
	return (0);
}

/*
* @brief: print the current working directory.
*/
int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd failed");
		return (1);
	}
}

/*
* @brief: exit minishell.
*/
int	builtin_exit(void)
{
	exit(0);
	return (0);
}

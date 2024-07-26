/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:30:36 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/26 16:03:23 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief: print arguments, -n no newline.
*/
void	builtin_echo(char **args)
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
}

/*
* @brief: change directory.
*/
void	builtin_cd(t_shell *shell, char **args)
{
	char	*home;

	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		home = get_env_value(shell->env_list, "HOME");
		if (home == NULL)
		{
			perror("cd: HOME not set\n");
			return ;
		}
		if (chdir(home) != 0)
			perror("cd failed");
	}
	else if (chdir(args[1]) != 0)
		perror("cd failed");
}

/*
* @brief: print the current working directory.
*/
void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd failed");
}

/*
* @brief: exit minishell.
*/
void	builtin_exit(void)
{
	exit(0);
}

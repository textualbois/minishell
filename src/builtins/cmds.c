/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:30:36 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/26 13:26:26 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	builtin_cd(t_shell *shell, char **args)
{
	char	*home;

	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		home = ft_get_env_value(shell->env_list, "HOME");
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

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("pwd failed");
}

// void	builtin_export(t_shell *shell, char **args) //todo check that smth like arg=new_var=with_equals works as in bash
// {
// 	char	**kv_pair;

// 	if (args[1] == NULL)
// 	{
// 		perror("export: no arguments\n");
// 		return ;
// 	}
// 	kv_pair = ft_split(args[1], '=');
// 	if (kv_pair && kv_pair[0] && kv_pair[1])
// 		ft_set_env_node(shell->env_list, kv_pair[0], kv_pair[1]);
// 	else
// 	{
// 		perror("export: invalid assigment\n");
// 		return ;
// 	}
// }

void	builtin_exit(void)
{
	exit(0);
}

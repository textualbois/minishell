/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:30:36 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/15 16:52:07 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **args) //todo figure out the -n flag
{
	int i;

	i = 1;
	if (ft_strcmp(args[1], "-n") == 0)
		i = 2;
	while (args[i] != NULL)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL) printf(" ");
		i++;
	}
	if (ft_strcmp(args[1], "-n") != 0)
		printf("\n");
}

void	builtin_cd(char **args)
{
	if (args[1] == NULL || chdir(args[1]) != 0)
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

void	builtin_export(t_shell *shell, char **args) //todo check that smth like arg=new_var=with_equals works as in bash
{
	char **kv_pair;

	if (args[1] != NULL)
	{
		//strtok??
		kv_pair = ft_split(args[1], '=');
		if (kv_pair && kv_pair[0] && kv_pair[1])
			ft_set_env_node(shell->env_list ,kv_pair[0], kv_pair[1]);
	}
}

void	builtin_exit(void)
{
	exit(0);
}
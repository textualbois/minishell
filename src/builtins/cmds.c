/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:30:36 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/14 16:07:14 by isemin           ###   ########.fr       */
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
* @brief: print the current working directory.
*/
int	builtin_pwd(void)
{
	char	cwd[1024];

	//printf("%s\n", getcwd(cwd, sizeof(cwd)));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd(cwd, 1);
		ft_putchar_fd('\n', 1);
		// printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd failed");
		return (1);
	}
}

/*
* @brief: exit minishell. // free some stuff.
*/
int	builtin_exit(t_shell *shell, t_command *cmd)
{
	int	ac;
	int	excode;

	ac = 0;
	excode = 0;
	while (cmd->args[ac])
		ac++;
	if (ac == 1)
	{
		excode = shell->exit_code;
		free_shell(shell, 0);
		exit(excode);
	}
	else
	{
		if (ft_isnum(cmd->args[1]))
		{
			excode = ft_atoi(cmd->args[1]);
			if (excode < 0)
				excode = 256 + excode;
			else if (excode > 255)
				excode = excode % 256;
			// shell->exit_code = excode;
			free_shell(shell, 0);
			exit(excode);
		}
		else
			return (printf("%s: numeric argument required\n",
					cmd->args[1]), exit(255), 255);
	}
}

int	ft_isnum(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

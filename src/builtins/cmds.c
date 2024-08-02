/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:30:36 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/02 19:27:04 by isemin           ###   ########.fr       */
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

// /*
// * @brief: change directory.
// */
// int	builtin_cd(t_shell *shell, char **args)
// {
// 	char	*dir;
// 	char	*oldpwd;
// 	char	*temp;

// 	oldpwd = get_env_value(shell->env_list, "PWD");
// 	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
// 	{
// 		dir = get_env_value(shell->env_list, "HOME");
// 		if (dir == NULL)
// 		{
// 			perror("cd: HOME not set\n");
// 			return (1);
// 		}
// 		else if (chdir(dir) != 0)
// 		{
// 			perror("cd failed");
// 			return (1);
// 		}
// 		else
// 		{
// 			oldpwd = ft_strjoin("OLDPWD=", oldpwd);
// 			builtin_export(shell, (char *[]){NULL, oldpwd, NULL});
// 			free(oldpwd);
// 			dir = ft_strjoin("PWD=", dir);
// 			builtin_export(shell, (char *[]){NULL, dir, NULL});
// 			free(dir);
// 			return (0);
// 		}
// 	}

// 	else if (ft_strcmp(args[1], "-") == 0)
// 	{
// 		printf("going back to previous directory\n");
// 		dir = get_env_value(shell->env_list, "OLDPWD");
// 		printf("dir: %s\n", dir);
// 		if (dir == NULL)
// 		{
// 			perror("cd: OLDPWD not set\n");
// 			return (1);
// 		}
// 		else if (chdir(dir) != 0)
// 		{
// 			perror("cd failed");
// 			return (1);
// 		}
// 		else
// 		{
// 			printf("%s\n", dir);
// 			oldpwd = ft_strjoin("OLDPWD=", oldpwd);
// 			builtin_export(shell, (char *[]){NULL, oldpwd, NULL});
// 			free(oldpwd);
// 			dir = ft_strjoin("PWD=", dir);
// 			builtin_export(shell, (char *[]){NULL, dir, NULL});
// 			free(dir);
// 			return (0);
// 		}
// 	}

// 	else if (chdir(args[1]) != 0)
// 	{
// 		perror("cd failed");
// 		return (1);
// 	}
// 	else
// 	{
// 		printf("got to %s\n", args[1]);
// 		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
// 		builtin_export(shell, (char *[]){NULL, oldpwd, NULL});
// 		free(oldpwd);
// 		dir = ft_strjoin("PWD=", args[1]);
// 		builtin_export(shell, (char *[]){NULL, dir, NULL});
// 		free(dir);
// 		return (0);
// 	}
// 	return (0);
// }

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

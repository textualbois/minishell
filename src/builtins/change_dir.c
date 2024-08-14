/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:05:09 by isemin            #+#    #+#             */
/*   Updated: 2024/08/14 21:10:39 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	change_dir_to_home(t_shell *shell, char *oldpwd)
{
	char	*dir;
	char	cwd[1024];

	dir = get_env_value(shell->env_list, "HOME");
	if (dir == NULL)
	{
		perror("cd: HOME not set\n");
		return (1);
	}
	else if (chdir(dir) != 0)
	{
		perror("cd failed");
		return (1);
	}
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		builtin_export(shell, (char *[]){NULL, oldpwd, NULL});
		free(oldpwd);
		getcwd(cwd, sizeof(cwd));
		dir = ft_strjoin("PWD=", cwd);
		builtin_export(shell, (char *[]){NULL, dir, NULL});
		free(dir);
		return (0);
	}
}

static int	change_dir_to_oldpwd(t_shell *shell, char *oldpwd)
{
	char	*dir;
	char	cwd[1024];

	dir = get_env_value(shell->env_list, "OLDPWD");
	if (dir == NULL || ft_strcmp(dir, "") == 0)
	{
		perror("cd: OLDPWD not set\n");
		return (1);
	}
	else if (chdir(dir) != 0)
	{
		perror("cd failed");
		return (1);
	}
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		builtin_export(shell, (char *[]){NULL, oldpwd, NULL});
		free(oldpwd);
		getcwd(cwd, sizeof(cwd));
		dir = ft_strjoin("PWD=", cwd);
		builtin_export(shell, (char *[]){NULL, dir, NULL});
		free(dir);
		return (0);
	}
}

static int	change_dir(t_shell *shell, char *dir, char *oldpwd)
{
	char	cwd[1024];

	printf("normal change_dird\n");
	if (chdir(dir) != 0)
	{
		perror("cd failed");
		return (1);
	}
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		builtin_export(shell, (char *[]){NULL, oldpwd, NULL});
		free(oldpwd);
		getcwd(cwd, sizeof(cwd));
		dir = ft_strjoin("PWD=", cwd);
		builtin_export(shell, (char *[]){NULL, dir, NULL});
		free(dir);
		return (0);
	}
}

/*
* @brief: change directory.
*/
int	builtin_cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	char	dir[1024];

	oldpwd = getcwd(dir, 1024);
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
		return (change_dir_to_home(shell, oldpwd));
	else if (ft_strcmp(args[1], "-") == 0)
		return (change_dir_to_oldpwd(shell, oldpwd));
	else
		return (change_dir(shell, args[1], oldpwd));
}

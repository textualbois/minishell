/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:28:51 by isemin            #+#    #+#             */
/*   Updated: 2024/08/15 02:54:29 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**sync_path(t_env *current_env);

static char	**sync_path(t_env *current_env)
{
	char	*path;
	char	**path_arr;
	char	**path_arr_temp;

	path = NULL;
	path_arr = NULL;
	while (current_env)
	{
		if (ft_strncmp(current_env->key, "PATH", 5) == 0)
		{
			path = current_env->value;
			break ;
		}
		current_env = current_env->next;
	}
	if (path == NULL)
		return (NULL);
	path_arr_temp = ft_split(current_env->value, ':');
	if (path_arr_temp != NULL)
	{
		path_arr = ft_map_s2a(path_arr_temp, "/\0", ft_strjoin);
		clear_arr(path_arr_temp);
	}
	return (path_arr);
}

/*
* @brief: create env list with the environment variables
* from the char **env wiht ft_split, key(name) is [0] and value is [1].
*/
t_env	*init_env_list(char **env)
{
	int		i;
	char	**kv_pair;
	t_env	*env_list;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		kv_pair = ft_split(env[i], '=');
		if (kv_pair)
		{
			if (kv_pair[0])
			{
				if (kv_pair[1] == NULL)
					kv_pair[1] = ft_strdup("");
				add_env_node(&env_list, kv_pair[0], kv_pair[1]);
			}
			free(kv_pair[0]);
			free(kv_pair[1]);
			free(kv_pair);
		}
		i++;
	}
	return (env_list);
}

/*
* @brief: create a new node and add to the list.
*/
int	add_env_node(t_env **env_list, char *key, char *value)
{
	t_env	*new;
	t_env	*current;

	new = malloc(sizeof(t_env));
	if (new == NULL)
	{
		perror("malloc failed");
		return (1);
	}
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (*env_list == NULL)
		*env_list = new;
	else
	{
		current = *env_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	return (0);
}

/*
* @brief: go through the env_list and update the shell->env with the new values.
* becouse changes are made to the env_list.
*/
char	**sync_env_from_list(t_env *env_list, t_shell *shell)
{
	t_env	*current_env;
	char	**env;
	int		i;
	char	*temp;

	current_env = env_list;
	env = malloc(sizeof(char *) * (token_count(env_list) + 1));
	if (env == NULL)
		return (printf("malloc failed"), NULL);
	i = 0;
	while (current_env)
	{
		temp = ft_strjoin(current_env->key, "=");
		if (!temp)
			return (printf("malloc failed"), NULL);
		env[i] = ft_strjoin(temp, current_env->value);
		free(temp);
		current_env = current_env->next;
		i++;
	}
	env[i] = NULL;
	if (shell->path != NULL)
		shell->path = clear_arr(shell->path);
	shell->path = sync_path(env_list);
	return (env);
}

/*
* @brief: call sync_env_from_list to go through the env_list and
* update the shell->env with the new values.
*/
void	update_env_shell(t_shell *shell)
{
	char	**env;

	env = sync_env_from_list(shell->env_list, shell);
	if (shell->env != NULL)
	{
		clear_arr(shell->env);
	}
	if (env == NULL)
		return ;
	shell->env = env;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:19:26 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/27 16:06:36 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @brief: print the environment list, add/update new var to list.
*/
int	builtin_export(t_shell *shell, char **args)
{
	char	**kv_pair;

	if (args[1] == NULL)
	{
		print_env_list(shell->env_list);
		return (0);
	}
	args++;
	while (*args != NULL)
	{
		kv_pair = ft_split(*args, '=');
		if (kv_pair[1] == NULL)
		{
			free(kv_pair);
			args++;
			continue ;
		}
		if (ft_get_env_value(shell->env_list, kv_pair[0]) == NULL)
			add_env_node(&shell->env_list, kv_pair[0], kv_pair[1]);
		else
			update_env_node(shell->env_list, kv_pair[0], kv_pair[1]);
		free(kv_pair);
		args++;
	}
	return (0);
}

/*
* @brief: sort and print the environment list.
*/
int	print_env_list(t_env *env_list)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		printf("%s=%s\n", current_env->key, current_env->value);
		current_env = current_env->next;
	}
	return (0);
}

/*
* @brief: update the value of an existing node.
*/
int	update_env_node(t_env *env_list, char *key, char *value)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		if (ft_strcmp(current_env->key, key) == 0)
		{
			free(current_env->value);
			current_env->value = ft_strdup(value);
			return (0);
		}
		current_env = current_env->next;
	}
	return (1);
}

/*
* @brief: create a new node and add sorted value to the list.
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
	{
		*env_list = new;
		return (0);
	}
	current = *env_list;
	while (current != NULL)
		current = current->next;
	current->next = new;
	return (0);
}

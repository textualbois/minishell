/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:19:18 by isemin            #+#    #+#             */
/*   Updated: 2024/08/15 02:20:25 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @brief: print the environment list. if any arguments are passed
* it will print an error message and return 127.
*/

int	builtin_env(t_shell *shell, char **args)
{
	t_env	*env_node;

	if (args[1] != NULL)
		return (printf("env: %s: No such file or directory\n",
				args[1]), 127);
	if (!shell->env_list)
		return (127);
	env_node = shell->env_list;
	while (env_node)
	{
		printf("%s=%s\n", env_node->key, env_node->value);
		env_node = env_node->next;
	}
	return (0);
}

/*
* @brief: unset a variable from the environment list.
* traverse the list and remove the node with matching key.
*/
int	builtin_unset(t_shell *shell, char *key)
{
	t_env	*current_env;
	t_env	*last_node;

	if (!shell->env_list || !key)
		return (1);
	current_env = shell->env_list;
	last_node = NULL;
	while (current_env)
	{
		if (ft_strcmp(current_env->key, key) == 0)
		{
			if (last_node)
				last_node->next = current_env->next;
			else
				shell->env_list = current_env->next;
			free_env_node(current_env);
			update_env_shell(shell);
			return (0);
		}
		last_node = current_env;
		current_env = current_env->next;
	}
	return (1);
}

/*
* @brief: get a variable from environment list.
*/
char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		if (ft_strcmp(current_env->key, key) == 0)
			return (current_env->value);
		current_env = current_env->next;
	}
	return (NULL);
}

/*
* @brief: free one node of the environment list.
*/
void	free_env_node(t_env *env_node)
{
	free(env_node->key);
	free(env_node->value);
	free(env_node);
}

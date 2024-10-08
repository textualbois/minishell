/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:19:18 by isemin            #+#    #+#             */
/*   Updated: 2024/08/09 13:33:33 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @brief: print the environment list. if any arguments are passed
* it will print an error message and return 127.
*/
int	builtin_env(t_shell *shell)
{
	t_env	*env_node;
	char	*input;

	input = shell->input;
	while (ft_isspace(*input))
		input++;
	if (ft_strcmp(input, "env") != 0)
	{
		printf("env: %s: No such file or directory\n", (input + 3));
		return (127);
	}
	if (!shell->env_list)
		return (127);
	env_node = shell->env_list;
	while (env_node)
	{
		if (env_node->value && *env_node->value)
		{
			printf("%s=%s\n", env_node->key, env_node->value);
		}
		env_node = env_node->next;
	}
	return (0);
}

/*
* @brief: unset a variable from the environment list.
* traverse the list and remove the node with matching key.
*/
int	builtin_unset(t_env **env_list, char *key)
{
	t_env	*last_node;
	t_env	*current_env;

	last_node = NULL;
	current_env = *env_list;
	if (!env_list || !key)
		return (1);
	while (current_env)
	{
		if (ft_strcmp(current_env->key, key) == 0)
		{
			if (last_node)
				last_node->next = current_env->next;
			else
				*env_list = current_env->next;
			free_env_node(current_env);
			if (ft_strcmp(key, "USER") == 0)
				form_prompt(NULL, "");
			return (0);
		}
		last_node = current_env;
		current_env = current_env->next;
	}
	return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:19:18 by isemin            #+#    #+#             */
/*   Updated: 2024/07/15 16:53:04 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// todo check how unset works
void	print_env(t_shell *shell)
{
	t_env	*env_node;

	env_node = shell->env_list;
	while (env_node)
	{
		if (env_node->value[0] == ' ' && ft_strlen(env_node->value))
		printf("%s=%s\n", env_node->key, env_node->value);
		env_node = env_node->next;
	}
}
// todo check if it should be env_list or shell->env_list
int	ft_set_env_node(t_env *env_list, char *key, char *value)
{
	t_env	*last_node;

	if (key == NULL)
		return (1);
	last_node = ft_unset_env_node(env_list, key);
	if (last_node == NULL)
	{
		last_node = get_tail(env_list);
		last_node->next = init_env_node(key, value);
		if (last_node->next == NULL)
			return (1);
	}
	else
	{
		last_node->value = ft_strdup(value);
		if (last_node->value == NULL)
			return (1);
	}
	return (0);
}

// todo check that it should be set to null and not ' '
// (see in bash maybe)
t_env	*ft_unset_env_node(t_env *env_list, char *key)
{
	t_env	*current_env;

	current_env = env_list;
	if (key != NULL)
		current_env = get_key_node(env_list, key);
	if (current_env == NULL)
		return (NULL);
	if (current_env->value != NULL)
	{
		free(current_env->value);
		current_env->value = NULL;
	}
	return (current_env);
}

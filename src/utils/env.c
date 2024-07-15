/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:10:04 by isemin            #+#    #+#             */
/*   Updated: 2024/07/15 16:16:08 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*get_tail(t_env *env_list)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env->next)
		current_env = current_env->next;
	return (current_env);
}

t_env	*get_key_node(t_env *env_list, char *key)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		if (ft_strcmp(current_env->key, key) && ft_strlen(current_env->key) == ft_strlen(key))
			return (current_env);
		current_env = current_env->next;
	}
	return (NULL);
}

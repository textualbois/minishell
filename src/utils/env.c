/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:10:04 by isemin            #+#    #+#             */
/*   Updated: 2024/08/07 13:23:33 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: return the last node of the list.
*/
t_env	*get_tail(t_env *env_list)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env->next)
		current_env = current_env->next;
	return (current_env);
}

/*
* @brief: get the respective node and return the value 
*	of the key from the environment list.
*/
t_env	*get_key_node(t_env *env_list, char *key)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		if (ft_strcmp(current_env->key, key)
			&& ft_strlen(current_env->key) == ft_strlen(key))
			return (current_env);
		current_env = current_env->next;
	}
	return (NULL);
}
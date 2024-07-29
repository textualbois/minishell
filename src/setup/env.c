/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:28:51 by isemin            #+#    #+#             */
/*   Updated: 2024/07/29 18:57:59 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *ft_getenv() // gets environment from char **env or some other way
{
	return (NULL);
}

/*
* @brief: init the env list with the environment variables
* from the char **env wiht ft_split, key(name) is [0] and value is [1].
*/
void	init_env_list(t_env **env_list, char **env)
{
	int		i;
	char	**kv_pair;

	i = 0;
	while (env[i])
	{
		kv_pair = ft_split(env[i], '=');
		if (kv_pair && kv_pair[0] && kv_pair[1])
			add_env_node(env_list, kv_pair[0], kv_pair[1]);
		if (kv_pair)
		{
			free(kv_pair[0]);
			free(kv_pair[1]);
			free(kv_pair);
		}
		i++;
	}
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

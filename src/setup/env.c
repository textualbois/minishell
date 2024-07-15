/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:28:51 by isemin            #+#    #+#             */
/*   Updated: 2024/07/15 15:00:27 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *ft_getenv() // gets environment from char **env or some other way
{
	return (NULL);
}

t_env	*init_env_node(char *key, char *value)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (env_node == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	env_node->key = key;
	env_node->value	= value;
	env_node->next = NULL;
	return (env_node);
}

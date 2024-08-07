/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:28:51 by isemin            #+#    #+#             */
/*   Updated: 2024/08/07 13:28:32 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
char	**sync_env_from_list(t_env *env_list) // not final
{
	t_env	*current_env;
	char	**env;
	int		i;
	char	*temp;
	temp = malloc(1000);

	current_env = env_list;
	i = 0;
	while (current_env)
	{
		i++;
		current_env = current_env->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		return (printf("malloc failed"), NULL);
	current_env = env_list;
	i = 0;
	while (current_env)
	{
		temp = ft_strjoin(current_env->key, "=");
		if (!temp)
			return (printf("malloc failed"), NULL);//free more each?
		env[i] = ft_strjoin(temp, current_env->value);
		free(temp);
		current_env = current_env->next;
	}
	env[i] = NULL;
	free(temp);
	return (env);
}

/*
* @brief: call sync_env_from_list to go through the env_list and
* update the shell->env with the new values. 
*/
void	update_env_shell(t_shell *shell)
{
	char	**env;

	env = sync_env_from_list(shell->env_list);
	if (env == NULL)
		return ;
	shell->env = env;
}

/*
* @brief: free the env_list.
*/
void	free_env_list(t_env *env_list)
{
	t_env	*current_env;
	t_env	*next_env;

	current_env = env_list;
	while (current_env)
	{
		next_env = current_env->next;
		free(current_env->key);
		free(current_env->value);
		free(current_env);
		current_env = next_env;
	}
}

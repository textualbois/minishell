/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:19:26 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/09 11:14:25 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
* @brief: print the environment list, add/update new var to list.
*/
int	builtin_export(t_shell *shell, char **args)
{
	char	**kv_pair;

	if (args[1] == NULL)
		return (print_env_list(shell->env_list), 0);
	args++;
	while (*args != NULL)
	{
		kv_pair = ft_split(*args, '=');
		if (kv_pair[1] == NULL)
			kv_pair[1] = ft_strdup("");
		if (get_env_value(shell->env_list, kv_pair[0]) == NULL)
			add_env_node(&shell->env_list, kv_pair[0], kv_pair[1]);
		else
			update_env_node(shell->env_list, kv_pair[0], kv_pair[1]);
		if (ft_strcmp(kv_pair[0], "USER") == 0)
			form_prompt(NULL, kv_pair[1]);
		free(kv_pair[0]);
		free(kv_pair[1]);
		free(kv_pair);
		args++;
	}
	update_env_shell(shell);
	return (0);
}

/*
* @brief: print the environment list.
*/
int	print_env_list(t_env *env_list)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		printf("declare -x %s=%s\n", current_env->key, current_env->value);
		current_env = current_env->next;
	}
	return (0);
}

/*
* @brief: update the value of an existing node.
*/
void	update_env_node(t_env *env_list, char *key, char *value)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		if (ft_strcmp(current_env->key, key) == 0)
		{
			free(current_env->value);
			current_env->value = ft_strdup(value);
			return ;
		}
		current_env = current_env->next;
	}
}

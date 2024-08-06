/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:30:39 by isemin            #+#    #+#             */
/*   Updated: 2024/08/06 14:11:21 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	init_env_list(&shell->env_list, env);
	if (getenv("USER") == NULL)
	{
		printf("TODO we should get user data on our own in this case\n");
		ft_getenv(); // todo get an environmnet through this. possibly generate some stuff.
	}
	else
	{
		shell->env = env;
		shell->user = getenv("USER");
		shell->cmd_paths = get_path(env);
	}
	shell->terminal_prompt = NULL;
	shell->exit_code = 0;
	shell->heredoc = NULL;
	shell->last_input = NULL;
	shell->terminal_prompt = NULL;
	shell->stdio_fds[0] = dup(STDIN_FILENO);
	shell->stdio_fds[1] = dup(STDOUT_FILENO);
	form_prompt(shell, shell->user);
}

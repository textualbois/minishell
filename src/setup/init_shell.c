/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:30:39 by isemin            #+#    #+#             */
/*   Updated: 2024/08/07 13:24:11 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// todo : get an env throu this? if its messing we need to generet it?
void	init_shell(t_shell *shell, char **env)
{
	if (getenv("USER") == NULL)
	{
		printf("TODO we should get user data on our own in this case\n");
	}
	else
	{
		shell->env = env;
		shell->user = getenv("USER");
		shell->cmd_paths = get_path(env);
	}
	shell->env_list = init_env_list(env);
	shell->terminal_prompt = NULL;
	shell->exit_code = 0;
	shell->heredoc = NULL;
	shell->last_input = NULL;
	shell->terminal_prompt = NULL;
	shell->stdio_fds[0] = dup(STDIN_FILENO);
	shell->stdio_fds[1] = dup(STDOUT_FILENO);
	form_prompt(shell, shell->user);
}

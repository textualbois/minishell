/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:30:39 by isemin            #+#    #+#             */
/*   Updated: 2024/08/07 17:46:58 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// todo : get an env throu this? if its messing we need to generet it?
void	init_shell(t_shell *shell, char **env)
{
	int		shlvl;
	char	*shlvl_str;
	char	*kv_pair;

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
	update_env_shell(shell);
	shlvl = ft_atoi(get_env_value(shell->env_list, "SHLVL"));
	shlvl_str = ft_itoa(shlvl + 1);
	kv_pair = ft_strjoin("SHLVL=", shlvl_str);
	builtin_export(shell, (char *[]){NULL, kv_pair, NULL});
	free(shlvl_str);
	free(kv_pair);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:30:39 by isemin            #+#    #+#             */
/*   Updated: 2024/08/09 12:25:06 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	if (getenv("USER") == NULL || getenv("PATH") == NULL)
	{
		printf(RED"No environment found. Exiting...\n"RESET);
		exit(1);
	}
	shell->env = env;
	shell->user = getenv("USER");
	shell->cmd_paths = get_path(env);
	shell->path = NULL;
	shell->env_list = init_env_list(env);
	shell->terminal_prompt = NULL;
	shell->exit_code = 0;
	shell->heredoc = NULL;
	shell->last_input = NULL;
	shell->terminal_prompt = NULL;
	shell->stdio_fds[0] = dup(STDIN_FILENO);
	shell->stdio_fds[1] = dup(STDOUT_FILENO);
	init_shell_env(shell);
}

void	init_shell_env(t_shell *shell)
{
	char	*shlvl_str;
	char	*kv_pair;
	int		shlvl;

	form_prompt(shell, shell->user);
	update_env_shell(shell);
	shlvl = ft_atoi(get_env_value(shell->env_list, "SHLVL"));
	shlvl_str = ft_itoa(shlvl + 1);
	kv_pair = ft_strjoin("SHLVL=", shlvl_str);
	builtin_export(shell, (char *[]){NULL, kv_pair, NULL});
	free(shlvl_str);
	free(kv_pair);
}

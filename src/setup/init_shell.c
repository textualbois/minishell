/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:30:39 by isemin            #+#    #+#             */
/*   Updated: 2024/08/12 13:03:01 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	init_shell(t_shell *shell, char **env)
// {
// 	if (getenv("USER") == NULL || getenv("PATH") == NULL)
// 	{
// 		printf(RED"No environment found. Exiting...\n"RESET);
// 		exit(1);
// 	}
// 	shell->env = env;
// 	shell->user = getenv("USER");
// 	shell->cmd_paths = get_path(env);
// 	shell->path = NULL;
// 	shell->env_list = init_env_list(env);
// 	shell->terminal_prompt = NULL;
// 	shell->exit_code = 0;
// 	shell->heredoc = NULL;
// 	shell->last_input = NULL;
// 	shell->terminal_prompt = NULL;
// 	shell->stdio_fds[0] = dup(STDIN_FILENO);
// 	shell->stdio_fds[1] = dup(STDOUT_FILENO);
// 	init_shell_env(shell);
// }

// void	init_shell_env(t_shell *shell)
// {
// 	char	*shlvl_str;
// 	char	*kv_pair;
// 	int		shlvl;

// 	form_prompt(shell, shell->user);
// 	update_env_shell(shell);
// 	shlvl = ft_atoi(get_env_value(shell->env_list, "SHLVL"));
// 	shlvl_str = ft_itoa(shlvl + 1);
// 	kv_pair = ft_strjoin("SHLVL=", shlvl_str);
// 	builtin_export(shell, (char *[]){NULL, kv_pair, NULL});
// 	free(shlvl_str);
// 	free(kv_pair);
// }
void    init_shell_env(t_shell *shell);
void    init_shell(t_shell *shell, char **env)
{
    // Check for essential environment variables
    if (getenv("USER") == NULL || getenv("PATH") == NULL || getenv("SHLVL") == NULL)
    {
        init_basic_env(shell);
    }
    else
    {
        // Initialize environment list and user from the existing environment
        shell->env_list = init_env_list(env);
        shell->user = getenv("USER");
        shell->cmd_paths = get_path(env);
    }
    shell->env = env; // Store the original environment pointer
    shell->path = NULL;
    shell->terminal_prompt = NULL;
    shell->exit_code = 0;
    shell->heredoc = NULL;
    shell->last_input = NULL;
    shell->stdio_fds[0] = dup(STDIN_FILENO);
    shell->stdio_fds[1] = dup(STDOUT_FILENO);
    // Initialize shell environment (SHLVL, prompt, etc.)
    init_shell_env(shell);
}
void    init_shell_env(t_shell *shell)
{
    char    *shlvl_str;
    char    *kv_pair;
    int     shlvl;
    // Form the terminal prompt based on user
    form_prompt(shell, shell->user);
    // Update shell environment variables
    update_env_shell(shell);
    // Update SHLVL (Shell Level)
    shlvl = ft_atoi(get_env_value(shell->env_list, "SHLVL"));
    shlvl_str = ft_itoa(shlvl + 1);
    kv_pair = ft_strjoin("SHLVL=", shlvl_str);
    builtin_export(shell, (char *[]){NULL, kv_pair, NULL});
    // Free allocated memory
    free(shlvl_str);
    free(kv_pair);
}
void    init_basic_env(t_shell *shell)
{
    // Initialize a basic environment with minimal variables
    shell->env_list = NULL;
    builtin_export(shell, (char *[]){"USER=default_user", NULL});
    shell->user = "default_user";
    builtin_export(shell, (char *[]){"PATH=/usr/bin:/bin", NULL});
    builtin_export(shell, (char *[]){"SHLVL=1", NULL});
}
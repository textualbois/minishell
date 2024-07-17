/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:18:53 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/17 12:37:54 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_command(t_shell *shell)
{
	(void)shell;
	int		i;

	i = -1;
	while (++i < shell->command_count)
	{
		/* code */
	}
	return (0);
}

/*
* @ brief: Processes a token, shuld execut the command
*/
void	handle_token(t_command *cmd, t_token *token)
{
	if (token->type == T_WORD)
		tokens_to_argv(cmd, token->value);
	else if (token->type == T_PIPE)
	{
		cmd->pipe_out = 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/10 17:17:59 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parse(t_shell *shell)
{
	int			cmd_index;
	int			i;
	t_command	*cmd;

	cmd_index = 0;
	i = -1;
	cmd = NULL;
	shell->commands = malloc(sizeof(t_command) * (shell->token_count + 1));
	if (!shell->commands)
		return (1);
	while (++i < shell->token_count)
	{
		if (shell->tokens[i].type == T_WORD)
		{
			if (!cmd)
			{
				cmd = malloc(sizeof(t_command));
				if (!cmd)
					return (1);
				ft_memset(cmd, 0, sizeof(t_command));
				shell->commands[cmd_index] = cmd;
			}
			if (!cmd->name)
				cmd->name = ft_strdup(shell->tokens[i].value);
			else
			{
				int arg_count = 0;
				while (cmd->args && cmd->args[arg_count])
					arg_count++;
				cmd->args = realloc(cmd->args, sizeof(char *) * (arg_count + 2));
				cmd->args[arg_count] = ft_strdup(shell->tokens[i].value);
				cmd->args[arg_count + 1] = NULL;
			}
		}
		else if (shell->tokens[i].type == T_PIPE)
			cmd = NULL;
		else if (shell->tokens[i].type == T_REDIRECT_IN)
		{
			if (i + 1 < shell->token_count && shell->tokens[i + 1].type == T_WORD)
			{
				if (cmd->input_file)
					free(cmd->input_file);
				cmd->input_file = ft_strdup(shell->tokens[++i].value);
			}
		}
		else if (shell->tokens[i].type == T_REDIRECT_OUT || shell->tokens[i].type == T_REDIRECT_APPEND)
		{
			if (i + 1 < shell->token_count && shell->tokens[i + 1].type == T_WORD)
			{
				if (cmd->output_file)
					free(cmd->output_file);
				cmd->output_file = ft_strdup(shell->tokens[++i].value);
				cmd->append_output = (shell->tokens[i - 1].type == T_REDIRECT_APPEND);
			}
		}
		else if (shell->tokens[i].type == T_HEREDOC)
		{
			if (i + 1 < shell->token_count && shell->tokens[i + 1].type == T_WORD)
			{
				if (cmd->heredoc_delimiter)
					free(cmd->heredoc_delimiter);
				cmd->heredoc_delimiter = ft_strdup(shell->tokens[++i].value);
			}
		}
		i++;
	}
	shell->commands[cmd_index] = NULL;
	shell->command_count = cmd_index + 1;
	return (0);
}

void	free_commands(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < shell->token_count)
	{
		if (shell->commands[i])
		{
			free(shell->commands[i]->name);
			while (shell->commands[i]->args && shell->commands[i]->args[++j])
				free(shell->commands[i]->args[j]);
			free(shell->commands[i]->args);
			free(shell->commands[i]->input_file);
			free(shell->commands[i]->output_file);
			free(shell->commands[i]->heredoc_delimiter);
			free(shell->commands[i]);
		}
	}
	free(shell->commands);
	shell->tokens = NULL;
	shell->token_count = 0;
}

void	free_tokens(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->token_count)
		free(shell->tokens[i].value);
	free(shell->tokens);
	shell->tokens = NULL;
	shell->token_count = 0;
}

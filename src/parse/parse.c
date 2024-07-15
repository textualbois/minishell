/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/15 17:16:04 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Parses the raw input string, tokenizes it 
*	and creates a list of commands.
*/
int	parse(t_shell *shell)
{
	if (quotes_check(shell) != 0)
	{
		printf("Error: unmatched quotes\n");
		return (1);
	}
	if (tokenize(shell, shell->raw_input) != 0)
	{
		printf("Error: tokenization failed\n");
		return (1);
	}
	if (process_tokens(shell) != 0)
	{
		printf("Error: command creation failed\n");
		return (1);
	}
	return (0);
}

/*
* @ brief: Checks if there are unmatched quotes in the input string.
*/
int	quotes_check(t_shell *shell)
{
	char	*input;
	int		single_quote;
	int		double_quote;

	input = shell->raw_input;
	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && !double_quote)
			single_quote = !single_quote;
		if (*input == '"' && !single_quote)
			double_quote = !double_quote;
		input++;
	}
	if (single_quote || double_quote)
		return (1);
	return (0);
}

/*
* @ brief: Creates a list of commands from the shell's token list.
*/
int	process_tokens(t_shell *shell)
{
	t_command	*new_cmd;
	int			i;
	int			start;

	shell->commands = NULL;
	shell->command_count = 0;
	i = -1;
	start = 0;
	while (++i < shell->token_count)
	{
		if (shell->tokens[i].type == T_PIPE || i == shell->token_count - 1)
		{
			if (i == shell->token_count - 1)
				i++;
			new_cmd = init_command(shell->tokens, start, i);
			if (!new_cmd || add_command(shell, new_cmd) != 0)
			{
				printf("Error: failed to initialize or add command\n");
				return (1);
			}
			start = i + 1;
		}
	}
	return (0);
}

/*
* @ brief: Creates a new command structure and initializes it.
*/
t_command	*init_command(t_token *tokens, int start, int end)
{
	t_command	*new_cmd;
	int			i;

	i = start -1;
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->pipe_out = 0;
	new_cmd->output_file = NULL;
	new_cmd->input_file = NULL;
	new_cmd->heredoc_delimiter = NULL;
	new_cmd->append_output = 0;
	while (++i < end)
	{
		handle_token(new_cmd, &tokens[i]);
	}
	return (new_cmd);
}

/*
* @brief: Adds a command to the shell's command list.
*/
int	add_command(t_shell *shell, t_command *new_cmd)
{
	t_command	**new_commands;
	int			i;

	i = -1;
	new_commands = malloc(sizeof(t_command *) * (shell->command_count + 1));
	if (!new_commands)
	{
		printf("Error: malloc failed in add_command\n");
		return (1);
	}
	while (++i < shell->command_count)
	{
		new_commands[i] = shell->commands[i];
	}
	new_commands[i] = new_cmd;
	free(shell->commands);
	shell->commands = new_commands;
	shell->command_count++;

	// Debug print for command addition
	printf("Command added: args = ");
	for (int j = 0; new_cmd->args && new_cmd->args[j]; j++)
	{
		printf("'%s' \n", new_cmd->args[j]);
	}
	return (0);
}

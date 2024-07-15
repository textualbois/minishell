/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/15 13:23:31 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Parses the raw input string, tokenizes it 
*	and creates a list of commands.
*/
int	parse(t_shell *shell)
{
	printf("Entering parse function\n"); //DEBUG
	if (quotes_check(shell) != 0)
	{
		printf("Error: unmatched quotes\n");
		return (1);
	}
	printf("Quotes handled successfully\n"); //DEBUG
	if (tokenize(shell, shell->raw_input) != 0)
	{
		printf("Error: tokenization failed\n");
		return (1);
	}
	printf("Tokenization completed successfully\n");	//DEBUG
	if(create_commands(shell) != 0)
	{
		printf("Error: command creation failed\n");
		return (1);
	}
	printf("Commands created successfully\n"); // DEBUG
	printf("Exiting parse function\n"); // DEBUG
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
int	create_commands(t_shell *shell)
{
	t_command	*new_cmd;
	int			i;
	int			start;

	shell->commands = NULL;
	shell->command_count = 0;
	start = 0;
	i = -1;
	while (++i < shell->token_count)
	{
		if (shell->tokens[i].type == T_PIPE || i == shell->token_count - 1)
		{
			if (i == shell->token_count - 1)
				i++;
            printf("Creating command from tokens %d to %d:\n", start, i - 1); // DEBUG
			new_cmd = create_command(shell, start, i);
			add_command(shell, new_cmd);
			start = i + 1;
		}
	}
	return (0);
}


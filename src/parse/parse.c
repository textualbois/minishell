/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/11 16:13:12 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parse(t_shell *shell)
{
	 // Step 1: Check for quotes
	printf("Entering parse function\n");
	if (handle_quotes(shell) != 0)
	{
		printf("Error: unmatched quotes\n");
		return (1);
	}
	printf("Quotes handled successfully\n");
	// step 2: Tokenize
	if (tokenize(shell, shell->raw_input) != 0)
	{
		printf("Error: tokenization failed\n");
		return (1);
	}
	printf("Tokenization completed successfully\n");	
	// step 3: create commands list from tokens
	// if(create_commands(shell) != 0)
	// {
	// 	printf("Error: command creation failed\n");
	// 	return (1);
	// }
	printf("Exiting parse function\n");
	return (0);
}

int	handle_quotes(t_shell *shell)
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

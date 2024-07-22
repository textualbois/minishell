/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/22 14:50:55 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Parses the raw input string, tokenizes it 
*	and creates a list of commands.
*/
int	parse(t_shell *shell)
{
	if (syntax_check(shell->raw_input) != 0)
	{
		return (1);
	}
	if (tokenize(shell, shell->raw_input) != 0)
	{
		printf("Error: tokenization failed\n");
		return (1);
	}
	if (shell->token_count > 0)
	{
		shell->ast = get_nodes_and_or(shell->head, NULL, NULL);
		if (!shell->ast)
		{
			printf("Error: failed to build AST\n");
			return (1);
		}
	}
	else
	{
		shell->ast = NULL;
	}
	return (0);
}

/*
* @ brief: Checks for syntax errors in the input string.
*/
int	syntax_check(char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	if (quotes_a_parentheses(input) != 0)
	{
		printf("Error: unmatched quotes or parentheses\n");
		return (1);
	}
	if (invalid_syntax(input) != 0)
	{
		printf("Error: invalid syntax\n");
		return (1);
	}
	//more syntax error?
	return (0);
}

/*
* @ brief: Checks if there are unmatched quotes in the input string.
*/
int	quotes_a_parentheses(char *input)
{
	int		single_quote;
	int		double_quote;
	int		open_parentheses;

	single_quote = 0;
	double_quote = 0;
	open_parentheses = 0;
	while (*input++)
	{
		if (*input == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*input == '"' && !single_quote)
			double_quote = !double_quote;
		else if (*input == '(' && !single_quote && !double_quote)
			open_parentheses++;
		else if (*input == ')' && !single_quote && !double_quote)
			open_parentheses--;
		if (open_parentheses < 0)
			return (1);
	}
	if (single_quote || double_quote || open_parentheses)
		return (1);
	return (0);
}

/*
* @ brief: Checks if there are invalid pipes and ampersands.
*/
int	invalid_syntax(char *input)
{
	if (*input == '|' || *input == '&')
		return (1);
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		if (*input == '|')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '|' || *input == '\0' || *input == '&')
				return (1);
		}
		else if (*input == '&')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input == '|' || *input == '&' || *input == '\0')
				return (1);
		}
		input++;
	}
	return (0);
}

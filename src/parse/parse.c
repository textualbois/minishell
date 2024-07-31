/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/31 15:40:16 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	here_doc_syntax(char *input);
/*
* @ brief: Parses the raw input string, tokenizes it
*	and creates AST.
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
			perror("Error: failed to build AST\n");
			return (1);
		}
		// else
		// {
		// 	printf("got an ast- all ok)\n");
		// }
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
	if (check_start_end(input) != 0)
		return (1);
	if (quotes_a_parentheses(input) != 0)
		return (1);
	if (check_consecutive_operators(input) != 0)
	{
		printf("Error: invalid syntax\n");
		return (1);
	}
	// if (here_doc_syntax(input) != 0)
	// {
	// 	printf("Error: invalid syntax\n");
	// 	return (1);
	// }
	return (0);
}

int	here_doc_syntax(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] && ft_isspace(input[i]))
				i++;
			if (!input[i] || ft_is_special_char(input[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

/*
* @ brief: Checks if the input string starts or ends with
*	a pipe or ampersand.
*/
int	check_start_end(char *input)
{
	char	*end;

	while (*input && ft_isspace(*input))
		input++;
	if (*input == '|' || *input == '&')
	{
		printf("Error: invalid syntax\n");
		return (1);
	}
	end = input + ft_strlen(input) - 1;
	while (end > input && ft_strlen(end))
		end--;
	if (*end == '|' || *end == '&')
	{
		printf("Error: invalid syntax\n");
		return (1);
	}
	return (0);
}

/*
* @ brief: Checks if there are unmatched quotes or
*	parentheses in the input string.
*/
int	quotes_a_parentheses(char *input)
{
	int		single_quote;
	int		double_quote;
	int		open_parentheses;

	single_quote = 0;
	double_quote = 0;
	open_parentheses = 0;
	while (*input)
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
		input++;
	}
	if (single_quote || double_quote || open_parentheses)
		return (1);
	return (0);
}

/*
* @ brief: Checks if there are invalid pipes and ampersands.
*/
int	check_consecutive_operators(char *input)
{
	int		i;
	int		operator_count;

	i = 0;
	operator_count = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '&')
		{
			operator_count++;
			if (operator_count > 2)
				return (1);
			if (operator_count == 2 && input[i] != input[i - 1])
				return (1);
		}
		else if (!ft_isspace(input[i]))
		{
			operator_count = 0;
		}
		i++;
	}
	return (0);
}

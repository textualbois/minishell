/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/07/11 16:13:34 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shell_loop(t_shell *shell)
{
	while (true)
	{
		form_prompt(shell);
		if (ft_readline(shell) == NULL) // should be null on ctrl+d
		{
			printf("Exiting shell.\n");
			break ;
		}
		char *trimmed_input = shell->raw_input; // Trim leading whitespace
		while (*trimmed_input && (*trimmed_input == ' ' || *trimmed_input == '\t'))
			trimmed_input++;
		if (*trimmed_input == '\0') // Skip empty input
		{
			free(shell->raw_input);
			continue ;
		}
		printf("raw_input: %s\n", trimmed_input);
		int parse_result = parse(shell);
		if (parse_result == 0)
		{
			printf("Tokenization result:\n");
			for (int i = 0; i < shell->token_count; i++)
			{
				printf("Token %d: Type = ", i);
				if (shell->tokens[i].type == T_WORD)
					printf("WORD");
				else if (shell->tokens[i].type == T_PIPE)
					printf("PIPE");
				else if (shell->tokens[i].type == T_REDIRECT_IN)
					printf("REDIRECT_IN");
				else if (shell->tokens[i].type == T_REDIRECT_OUT)
					printf("REDIRECT_OUT");
				else if (shell->tokens[i].type == T_HEREDOC)
					printf("HEREDOC");
				else if (shell->tokens[i].type == T_REDIRECT_APPEND)
					printf("REDIRECT_APPEND");
				else
					printf("UNKNOWN");
				printf(", Value = '%s'\n", shell->tokens[i].value);
			}
		}
		else
		{
			printf("Parsing failed with error code: %d\n", parse_result);
		}    
		free_tokens(shell);
		free(shell->raw_input);
	}
	return (0);
}

//readline works if stdin has not been redirected or messed with
// so for that case use get_next_line maybe
void	*ft_readline(t_shell *shell) //readline works if stdin has not been redirected or messed with
{
	shell->raw_input = readline(shell->terminal_prompt); //shows prompt and reads line
	if (shell->raw_input == NULL)
	{
		printf("readline gave null\n");
		return (NULL);
	}
	if (*(shell->raw_input) != 0)
		add_history(shell->raw_input);
	return ((void *)1);
}

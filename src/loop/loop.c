/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/07/16 17:47:59 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shell_loop(t_shell *shell)
{
	char	*t_input;

	while (42)
	{
		form_prompt(shell);
		if (ft_readline(shell) == NULL)
		{
			printf("Exiting shell.\n");
			break ;
		}
		t_input = shell->raw_input;
		while (*t_input && (*t_input == ' ' || *t_input == '\t'))
			t_input++;
		if (*t_input == '\0')
		{
			free(shell->raw_input);
			continue ;
		}
		printf("raw_input: %s\n", t_input); //DEBUG
		if (parse(shell) != 0)
		{
			printf("Parsing failed\n");
			free(shell->raw_input);
			continue ;
		}
		printf("Tokenization result:\n"); //DEBUG
		for (int i = 0; i < shell->token_count; i++) // DEBUG
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
			else if (shell->tokens[i].type == T_OR)
   				 printf("OR");
			else if (shell->tokens[i].type == T_AND)
				printf("AND");
			else
				printf("UNKNOWN");
			printf(", Value = '%s'\n", shell->tokens[i].value);
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

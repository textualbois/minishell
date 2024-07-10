/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/10 14:00:28 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parse(t_shell *shell)
{
	int	cmd_index;
	int	token_index;

	cmd_index = 0;
	token_index = 0;
	shell->commands = malloc(sizeof(t_command) * (shell->token_count + 1));
	if (!shell->commands)
		return (1);
	
	while (token_index < shell->token_count)
	{
		t_command *cmd = malloc(sizeof(t_command));
		if (!cmd)
			return (1);
		
		if (shell->tokens[i].type == T_WORD)
			printf("doing stuff with word: %s\n", shell->tokens[i].value);
		else if (shell->tokens[i].type == T_PIPE)
			printf("doing stuff with pipe\n");
		else if (shell->tokens[i].type == T_REDIRECT_IN)
			printf("doing stuff with redirect in\n");
		else if (shell->tokens[i].type == T_REDIRECT_OUT)
			printf("doing stuff with redirect out\n");
		else if (shell->tokens[i].type == T_REDIRECT_APPEND)
			printf("doing stuff with redirect append\n");
		else if (shell->tokens[i].type == T_HEREDOC)
			printf("doing stuff with heredoc\n");
    	for (int i = -1; i < shell->token_count; ++i)
    	{
    	   printf("Token %d: Type %d, Value: %s\n", i, shell->tokens[i].type, shell->tokens[i].value);
    	    // Add parsing logic here
    	}
	}
	return (0);
}

void	free_tokens(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->token_count)
	{
		free(shell->tokens[i].value);
	}
	free(shell->tokens);
	shell->tokens = NULL;
	shell->token_count = 0;
}

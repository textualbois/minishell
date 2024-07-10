/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/07/10 13:54:18 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shell_loop(t_shell	*shell)
{
	while (true)
	{
		form_prompt(shell);
		if (ft_readline(shell) == NULL) //should be null on ctrl+d
			break ;
		if (!tokenize(shell, shell->raw_input))
		{
			free(shell->raw_input);
			return (ft_error(shell, 1));
		}
		if(!parse(shell))
		{
			free(shell->raw_input);
			free_tokens(shell);
			return (ft_error(shell, 2));
		}
		for (int i = 0; i < shell->token_count; i++) // debug
		{
			printf("token %d: %s\n", i, shell->tokens[i].value);
		}
		//execute_commands(shell); // execut parsed cmd
		free(shell->raw_input);
		free_tokens(shell);
		int i =-1;
		while (++i < shell->commands[i])
		{
			free(shell->commands[i]);
		}
		free(shell->commands);
	}
	return (0);
}

//readline works if stdin has not been redirected or messed with
// so for that case use get_next_line maybe
void	*ft_readline(t_shell *shell) //readline works if stdin has not been redirected or messed with
{
	//char	*line;

	shell->raw_input = readline(shell->terminal_prompt); //shows prompt and reads line
	if (shell->raw_input == NULL)
	{
		printf("readline gave null\n");
		return (NULL);
	}
	// if (*(shell->raw_input) != 0)
	// 	add_history(shell->raw_input);
	return ((void *)1);
}

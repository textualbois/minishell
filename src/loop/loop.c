/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/07/09 17:15:14 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shell_loop(t_shell	*shell)
{
	t_data	data;
	while (true)
	{
		form_prompt(shell);
		if (ft_readline(shell) == NULL) //should be null on ctrl+d
			break ;
		if (!tokenize(&data, shell->input_prompt))
		{
			free(shell->input_prompt);
			return (ft_error(&data, 1));
		}
		for (int i = 0; i < data.token_count; i++) // debug
		{
			printf("token %d: %s\n", i, data.tokens[i].value);
		}
		// parsing adn exewcution
		printf("doing stuff with input:\n");
		// free(shell->input_prompt);
		// free(data.tokens);
		printf("%s\n", shell->input_prompt);
	}
	return (0);
}

//readline works if stdin has not been redirected or messed with
// so for that case use get_next_line maybe
void	*ft_readline(t_shell *shell) //readline works if stdin has not been redirected or messed with
{
	//char	*line;

	shell->input_prompt = readline(shell->terminal_prompt); //shows prompt and reads line
	if (shell->input_prompt == NULL)
	{
		printf("readline gave null\n");
		return (NULL);
	}
	return ((void *)1);
}

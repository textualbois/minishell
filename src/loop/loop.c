/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/07/10 17:32:17 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shell_loop(t_shell	*shell)
{
	char	**splitted_input;
	int		i;
	
	
	while (true)
	{
		form_prompt(shell);
		if (ft_readline(shell) == NULL) //should be null on ctrl+d
			break ;
		printf("raw_input: %s\n", shell->raw_input);
		splitted_input = ft_split(shell->raw_input, '|');
		i = 0;
		while (splitted_input[i])
		{
			printf("splitted_input[%d]: %s\n", i, splitted_input[i]);
			i++;
		}
		if (tokenize(shell, shell->raw_input) == 0)
		{
			if (parse(shell) == 0)
			{
				//execution here
			}
			free_commands(shell);
			free_tokens(shell);
		}
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

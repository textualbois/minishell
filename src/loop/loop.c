/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/07/08 15:48:21 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shell_loop(t_shell	*shell)
{
	while (true)
	{
		form_prompt(shell);
		while (ft_readline(shell) == NULL) //should be null on ctrl+d
			break ;
		printf("doing stuff with input:\n");
		printf("%s\n", shell->input_prompt);
	}
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

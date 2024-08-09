/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/08/09 10:59:53 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shell_loop(t_shell *shell)
{
	char	*t_input;

	signal_handlers();
	while (42)
	{
		form_prompt(shell, NULL);
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
		if (parse(shell) != 0)
		{
			printf("Parsing failed\n");
			free(shell->raw_input);
			continue ;
		}
		else
		{
			shell->exit_code = execute_ast(shell, shell->ast, EXIT_SUCCESS);
			free_tokens(shell);
			free(shell->raw_input);
		}
	}
	return (0);
}

//readline works if stdin has not been redirected or messed with
// so for that case use get_next_line maybe
//readline works if stdin has not been redirected or messed with
// readline ()  -  shows prompt and reads line
void	*ft_readline(t_shell *shell)
{
	shell->raw_input = readline(shell->terminal_prompt);
	if (shell->raw_input == NULL)
	{
		printf("readline gave null\n");
		return (NULL);
	}
	if (*(shell->raw_input) != 0)
		add_history(shell->raw_input);
	return ((void *)1);
}

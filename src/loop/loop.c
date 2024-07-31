/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/07/31 10:16:45 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	shell_loop(t_shell *shell)
{
	char	*t_input;

	shell->is_parent_process = true;
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
		printf("raw_input: %s\n", t_input); //DEBUG
		if (parse(shell) != 0)
		{
			printf("Parsing failed\n");
			free(shell->raw_input);
			continue ;
		}
		else
		{
			//expand_wildcard_tokens(shell); // call before expand_dollar_tokens
			expand_dollar_tokens(shell); //call before print_ast
			print_ast(shell);
			shell->exit_code = execute_ast(shell, shell->ast, EXIT_SUCCESS);
			free_tokens(shell);
			free(shell->raw_input);
		}
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

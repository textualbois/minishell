/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/08/09 14:03:11 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
* @brief : set up the signal handler, int status for input handle
*	parse the input and execute the ast.
*/
int	shell_loop(t_shell *shell)
{
	int	input_status;

	signal_handlers();
	while (42)
	{
		form_prompt(shell, NULL);
		input_status = handle_input(shell);
		if (input_status == -2)
			break ;
		if (input_status == -1)
			continue ;
		if (parse(shell) != 0)
		{
			printf("Parsing failed\n");
			free(shell->input);
			continue ;
		}
		else
		{
			printf("hehe i passed the parse\n");
			shell->exit_code = execute_ast(shell, shell->ast, EXIT_SUCCESS);
			printf("hehe i passed the execution\n");
			free_tokens(shell);
			free(shell->input);
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
	shell->input = readline(shell->terminal_prompt);
	if (shell->input == NULL)
	{
		printf("readline gave null\n");
		return (NULL);
	}
	if (*(shell->input) != 0)
		add_history(shell->input);
	return ((void *)1);
}

/*
* @brief: if readlien give NULL it means is EOF and we return -2
*	to shell loop, if the input is empty we return - 1, free 
*	shell input and continut the loop. or 0 for a valid input.
*/
int	handle_input(t_shell *shell)
{
	char	*t_input;
	char	*o_input;

	if (ft_readline(shell) == NULL)
	{
		printf("Exiting shell.\n");
		return (-2);
	}
	o_input = shell->input;
	t_input = o_input;
	while (*t_input && (*t_input == ' ' || *t_input == '\t'))
		t_input++;
	if (*t_input == '\0')
	{
		free(o_input);
		return (-1);
	}
	if (t_input != o_input)
	{
		shell->input = ft_strdup(t_input);
		free(o_input);
		if (!shell->input)
			return (-2);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/08/14 17:54:08 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_env_array_loop(char **env)
{
	int	i = 0;
	if (env == NULL)
	{
		printf("Environment array is NULL.\n");
		return ;
	}
	while (env[i] != NULL)
	{
		printf("env[%d]: %s\n", i, env[i]);
		i++;
	}
}

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
		// print_env_array_loop(shell->env); //debug
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
			shell->exit_code = execute_ast(shell, shell->ast, EXIT_SUCCESS);
		free_tokens(shell);
		free_ast(shell->ast);
		free(shell->input);
	}
	//free_tokens(shell);
	free_shell(shell, input_status);
	printf("Exiting shell1231231232erwfdz.\n");
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
	int		ret;

	if (ft_readline(shell) == NULL)
	{
		printf("Exiting shell.\n");
		return (-2);
	}
	ret = trim_and_free_input(shell);
	if (ret != 0)
		return (ret);
	return (0);
}

/*
* @brief: o_input is the original input, t_input is the trimmed input.
*	If the trimmed input is empty, free the original input and return -1.
*	If the trimmed input is different from the original input,
*	allocate a new string and copy the trimmed input. Free the original input.
*/
int	trim_and_free_input(t_shell *shell)
{
	char	*o_input;
	char	*t_input;

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
		if (!shell->input)
		{
			free(o_input);
			return (-2);
		}
		free(o_input);
	}
	return (0);
}

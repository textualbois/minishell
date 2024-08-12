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

void	*ft_readline_further(t_shell *shell)
{
	char	*extra_line;
	char	*old_input;
	
	old_input = shell->input;
	extra_line = readline("> ");
	if (shell->input == NULL)
	{
		printf("readline gave null\n");
		return (NULL);
	}
	shell->input = ft_strjoin(old_input, extra_line);
	free(old_input);
	free(extra_line);
	if (*(shell->input) != 0)
		add_history(shell->input);
	return ((void *)1);
}

int prompt_further(t_shell *shell)
{
	char	*t_input;
	char	*o_input;

	if (ft_readline_further(shell) == NULL)
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
	return (parse(shell));
}

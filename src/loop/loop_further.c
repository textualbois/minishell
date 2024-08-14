/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_further.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:02:02 by isemin            #+#    #+#             */
/*   Updated: 2024/08/14 21:41:42 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_readline_further(t_shell *shell)
{
	char	*extra_line;
	char	*old_input;

	old_input = shell->input;
	extra_line = readline("> ");
	if (extra_line == NULL)
		return (NULL);
	if (old_input == NULL)
	{
		shell->input = extra_line;
		return ((void *)1);
	}
	shell->input = ft_strjoin(old_input, extra_line);
	free(old_input);
	free(extra_line);
	if (*(shell->input) != 0)
		add_history(shell->input);
	return ((void *)1);
}

int	prompt_further(t_shell *shell)
{
	int	ret;

	if (ft_readline_further(shell) == NULL)
		return (-2);
	ret = trim_and_free_input(shell);
	if (ret != 0)
		return (ret);
	return (parse(shell));
}

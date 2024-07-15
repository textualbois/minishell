/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:05:39 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/15 17:11:09 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Determines the type of a token based on char.
*/
t_tokentype	get_token_type(char *str)
{
	if (ft_strncmp(str, "|", 1) == 0)
		return (T_PIPE);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (T_REDIRECT_IN);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (T_REDIRECT_OUT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (T_HEREDOC);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (T_REDIRECT_APPEND);
	else
		return (T_WORD);
}

void	free_tokens(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->token_count)
		free(shell->tokens[i].value);
	free(shell->tokens);
	shell->tokens = NULL;
	shell->token_count = 0;
}

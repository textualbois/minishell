/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:05:39 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/17 17:58:59 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Determines the type of a token based on char.
*/
// t_tokentype	get_token_type(char *str)
// {
// 	if (*str == '|')
// 	{
// 		if (*(str + 1) == '|')
// 			return (T_OR);
// 		else
// 			return (T_PIPE);
// 	}
// 	else if (*str == '<')
// 	{
// 		if (*(str + 1) == '<')
// 			return (T_HEREDOC);
// 		else
// 			return (T_REDIRECT_IN);
// 	}
// 	else if (*str == '>')
// 	{
// 		if (*(str + 1) == '>')
// 			return (T_REDIRECT_APPEND);
// 		else
// 			return (T_REDIRECT_OUT);
// 	}
// 	else if (*str == '&' && *(str + 1) == '&')
// 		return (T_AND);
// 	else
// 		return (T_WORD);
// }
// t_tokentype	get_token_type(char *str)
// {
// 	if (*str == '|')
// 	{
// 		if (*(str + 1) == '|')
// 			return (T_OR);
// 		else
// 			return (T_PIPE);
// 	}
// 	else if (*str == '&' && *(str + 1) == '&')
// 		return (T_AND);
// 	else if ((*str == '<' && *(str + 1) == '<')
// 		|| (*str == '>' && *(str + 1) == '>' ))
// 		return (T_SPECIAL);
// 	else if (*str == '<' || *str == '>')
// 		return (T_SPECIAL);
// 	else if (*str == '"' || *str == '\'')
// 		return (T_QUOTE);
// 	else
// 		return (T_WORD);
// }

t_tokentype	get_token_type(char *str)
{
	if (*str == '|')
	{
		if (*(str + 1) == '|')
			return (T_OR);
		else
			return (T_PIPE);
	}
	else if (*str == '&' && *(str + 1) == '&')
		return (T_AND);
	else if ((*str == '<' && *(str + 1) == '<')
		|| (*str == '>' && *(str + 1) == '>' ))
		return (T_SPECIAL);
	else if (*str == '"' || *str == '\'')
		return (T_QUOTE);
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

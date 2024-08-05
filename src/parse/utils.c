/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:05:39 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/05 13:59:33 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


/*
* @ brief: Determines the type of a token based on char.
*/
t_tokentype	get_token_type(char *str)
{
	if (*str == '|')
	{
		if (*(str + 1) == '|')
			return (T_OR);
		else
			return (T_PIPE);
	}
	else if (*str == '&' || (*str == '&' && *(str + 1) == '&'))
		return (T_AND);
	else if (*str == '<' || (*str == '<' && *(str + 1) == '<'))
		return (T_SPECIAL);
	else if (*str == '>' || (*str == '>' && *(str + 1) == '>'))
		return (T_SPECIAL);
	else if (*str == '"' || *str == '\'')
		return (T_QUOTE);
	else if (*str == '$' && *(str + 1) == '?')
		return (T_EXCODE);
	else if (*str == '$')
		return (T_DOLLAR);
	else
		return (T_WORD);
}

/*
* @ brief: clears the shell's token list.
*/
void	free_tokens(t_shell *shell)
{
	t_token	*current;
	t_token	*next;

	current = shell->head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	shell->head = NULL;
	shell->tail = NULL;
	shell->token_count = 0;
}

/*
* @ brief: Checks if there are invalid heredoc syntax.
*/
int	check_heredoc_syntax(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] && ft_isspace(input[i]))
				i++;
			if (!input[i] || ft_is_special_char(input[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

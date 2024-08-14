/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:05:39 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/14 21:32:44 by mrusu            ###   ########.fr       */
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
	else if (*str == '"')
		return (T_DQUOTE);
	else if (*str == '\'')
		return (T_SQUOTE);
	else if (*str == '$' && *(str + 1) == '?')
		return (T_EXCODE);
	else if (*str == '$')
		return (T_DOLLAR);
	else
		return (T_WORD);
}

/*
* @brief: return the count of tokens in the env_list.
*/
int	token_count(t_env *env_list)
{
	t_env	*current_env;
	int		count;

	current_env = env_list;
	count = 0;
	while (current_env)
	{
		count++;
		current_env = current_env->next;
	}
	return (count);
}

/*
* @ brief: when char < or > is meet, this function is called to check if the
*	redirect syntax is valid. valid means no more than 2 consecutive < or >.
* 	also, the next char after the redirect symbol should not be a space or
* 	a special char. we expect a word after the redirect symbol.
*/
int	check_redirect_syntax(char *input, int *i)
{
	int		j;
	int		redirect_count;

	j = *i;
	redirect_count = 0;
	while (input[j] == '>' || input[j] == '<')
	{
		redirect_count++;
		if (redirect_count > 2)
		{
			printf("Error: invalid redirect syntax\n");
			return (1);
		}
		j++;
	}
	while (input[j] && ft_isspace(input[j]))
		j++;
	if (!input[j] || ft_is_special_char(input[j]))
	{
		printf("Error: invalid redirect syntax\n");
		return (1);
	}
	*i = j;
	return (0);
}

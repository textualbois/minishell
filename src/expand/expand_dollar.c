/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:57:00 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/14 23:57:03 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @ brief: Expands the dollar tokens by replacing them with the value of the
*	variables they represent, based on tokens type.
*/
void	expand_dollar_tokens(t_shell *shell, t_token *current)
{
    printf("Tokens before expansion:\n");
    t_token *tmp = current;
    while (tmp)
    {
        printf("Token type: %d, Token value: %s\n", tmp->type, tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
	while (current)
	{
		if (current->type == T_WORD_EXPAND || current->type == T_DQUOTE)
		{
			printf("Handling word or dquote\n");
			handle_word_or_dquote(shell, current);
		}
		else if (current->type == T_SQUOTE)
		{
			printf("Handling single quote\n");
			handle_single_quote(current);
		}
		else if (current->type == T_DOLLAR)
		{
			printf("Handling dollar\n");
			process_dollar_token(shell, current, ft_strdup(current->value));
		}
		else if (current->type == T_EXCODE)
		{
			printf("Handling exit code\n");
			handle_exit_code(shell, current);
		}
		else if (ft_strchr(current->value, '*'))
		{
			current->type = T_WILDCARD;
		}
		else
		{
			current = current->next;
			continue ;
		}
		if (ft_strchr(current->value, '*'))
			current->type = T_WILDCARD;
		else
			current = fallback_on_prev_token(current);
		current = current->next;
	}
	printf("Tokens after expansion:\n");
	tmp = shell->head;
	while (tmp)
	{
		printf("Token type: %d, Token value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

/*
* @ brief: Handles a T_WORD_EXPAND or T_DQUOTE token by expanding the word.
*/
void	handle_word_or_dquote(t_shell *shell, t_token *token)
{
	char	*temp;
	int		q_c;

	q_c = 0;
	while (token->value[q_c] == '\'' || token->value[q_c] == '"')
		q_c++;
	printf("q_c: %d\n", q_c);
	if (token->value[q_c] == '$')
	{
		process_dollar_token(shell, token, ft_substr(token->value, q_c + 1, ft_strlen(token->value) - q_c - 1 - (q_c > 0)));
		if (q_c > 0)
		{
			temp = ft_strjoin_free(ft_strdup("\'"), token->value);
			free(token->value);
			token->value = ft_strjoin_free(temp, "\'");
		}
	}
	token->type = T_WORD;
	if (token->prev != NULL && token->prev->type == T_WORD)
		fallback_on_prev_token(token);
}

/*
* @ brief: Processes a T_DOLLAR token by getting the value of the variable
*	and replacing the token with a T_WORD token and the value.
*/
void	process_dollar_token(t_shell *shell, t_token *token, char *str)
{
	char	*value;

	value = get_env_value(shell->env_list, str);
	free(token->value);
	free(str);
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = ft_strdup("");
	token->type = T_WORD;
}

/*
* @ brief: Expands a word by replacing the variables with their values.
*/
char	*expand_word_token(t_shell *shell, const char *str)
{
	char	*result;
	int		i;
	int		in_dquote;
	char	*expanded;

	i = 0;
	in_dquote = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '"')
		{
			in_dquote = !in_dquote;
			i++;
		}
		else
		{
			expanded = expand_variables(shell, str, &i, in_dquote);
			result = ft_strjoin_free(result, expanded);
			free(expanded);
		}
	}
	return (result);
}

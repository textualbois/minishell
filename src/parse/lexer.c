/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:34:33 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/10 17:18:13 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	add_token(t_shell *shell, t_tokentype type, char *value)
{
	int		i;
	t_token	*new_tokens;

	i = -1;
	new_tokens = malloc(sizeof(t_token) * (shell->token_count + 1));
	if (!new_tokens)
	{
		perror("malloc failed in add_token");
		exit(1);
	}
	while (++i < shell->token_count)
	{
		new_tokens[i] = shell->tokens[i];
	}
	new_tokens[i].type = type;
	new_tokens[i].value = value;
	free(shell->tokens);
	shell->tokens = new_tokens;
	shell->token_count++;
}

int	tokenize(t_shell *shell, char *input)
{
	size_t	i;
	size_t	start;

	start = 0;
	i = -1;
	shell->tokens = NULL;
	shell->token_count = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		start = i;
		if (ft_is_special_char(input[i]))
		{
			if (ft_strncmp(input + i, "<<", 2) == 0 || ft_strncmp(input + i, ">>", 2) == 0)
				i += 2;
			else
				i++;
		}
		else
		{
			while (input[i] && !ft_isspace(input[i]) && !ft_is_special_char(input[i]))
				i++;
		}
		if (i > start)
			add_token(shell, get_token_type(input + start), ft_substr(input, start, i - start));
	}
	return (0);
}

char	**tokens_to_argv(t_shell *shell)
{
	char	**argv;
	int		i;

	i = -1;
	argv = malloc(sizeof(char *) * (shell->token_count + 1));
	if (!argv)
		return (NULL);
	while (++i < shell->token_count)
	{
		argv[i] = shell->tokens[i].value;
	}
	argv[shell->token_count] = NULL;
	return (argv);
}

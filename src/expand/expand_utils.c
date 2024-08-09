/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:53:14 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/09 11:01:55 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
* @ brief: Extracts the variable name from a string.
*	Iterates through the string until it finds a character that is not
*	an alphanumeric character or an underscore. 
*/
char	*extract_variable_name(const char *str, int *i)
{
	int		j;
	char	*var_name;

	if (!str || !i)
		return (NULL);
	j = *i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, *i + 1, j - (*i + 1));
	*i = j;
	return (var_name);
}

/*
* @ brief: repalces the variable with its value in the string.
*/
char	*expand_variables(t_shell *shell, const char *str,
			int *i, int in_dquote)
{
	char	*result;
	char	*var_name;
	char	*value;

	if (!str || !i)
		return (NULL);
	result = ft_strdup("");
	if (str[*i] == '$' && (in_dquote || (*i > 0 && str[*i - 1] != '\'')))
	{
		var_name = extract_variable_name(str, i);
		value = get_env_value(shell->env_list, var_name);
		if (value)
			result = ft_strjoin_free(result, value);
		free(var_name);
	}
	else
	{
		result = ft_strjoin_free_char(result, str[*i]);
		(*i)++;
	}
	return (result);
}

// Helper function to join strings and free the first one
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

// Helper function to join a string and a char, freeing the string
char	*ft_strjoin_free_char(char *s, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(s, tmp));
}

/*
* @ brief: check and skip the quotes in the string.
*/
int	handle_quotes(const char *str, int i, int *in_dquote)
{
	if (str[i] == '"')
	{
		*in_dquote = !(*in_dquote);
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:53:14 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/05 13:17:53 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
* @ brief: Extracts the variable name from a string.
*	Iterates through the string until it finds a character that is not
*	an alphanumeric character or an underscore. 
*/
char	*extract_variable_name(char *str, int *i)
{
	int		j;
	char	*var_name;

	j = *i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, *i + 1, j - (*i + 1));
	*i = j;
	return (var_name);
}

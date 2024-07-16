/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:22:09 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/16 13:56:32 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_arrdup(char **arr)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = ft_calloc((i + 1), sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			while (i > 0)
				free(new_arr[--i]);
			free(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f');
}

int	ft_is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

static int	convert_ascii(int i) // maybe replace with typecasting to char
{
	if (i < 0)
		return (256 - i);
	return (i);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (convert_ascii(str1[i]) - convert_ascii(str2[i])); // maybe replace with typecasting to char
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:22:09 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/15 02:16:23 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
* @brief: duplicate a string.
*/
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

/*
* @brief: check if a char is a space.
*/
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f');
}

/*
* @brief: check a char from a string and if return if it is a special char.
*/
int	ft_is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == ';'
		|| c == '(' || c == ')');
}

/*
* @brief: convert to unsigned char adn then compare two strings.
*	return 0 if the strings are equal, otherwise the difference > 1.
*/
int	ft_strcmp(const char *str1, const char *str2)
{
	size_t			i;
	unsigned char	*u_str1;
	unsigned char	*u_str2;

	i = 0;
	u_str1 = (unsigned char *)str1;
	u_str2 = (unsigned char *)str2;
	while (u_str1[i] != '\0' || u_str2[i] != '\0')
	{
		if (u_str1[i] != u_str2[i])
			return (u_str1[i] - u_str2[i]);
		i++;
	}
	return (0);
}

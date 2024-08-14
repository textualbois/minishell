/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:11:50 by isemin            #+#    #+#             */
/*   Updated: 2024/08/14 17:04:07 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_arrlen(char **arr)
{
	size_t	res;

	res = 0;
	while (arr[res] != NULL)
		res++;
	return (res);
}

void	*clear_arr(char **res_arr)
{
	size_t	count;
	size_t	arr_len;

	count = 0;
	arr_len = ft_arrlen(res_arr);
	while (count < arr_len)
	{
		if (res_arr[count] != NULL)
			free(res_arr[count]);
		res_arr[count] = NULL;
		count++;
	}
	if (res_arr != NULL)
		free(res_arr);
	res_arr = NULL;
	return (NULL);
}

char	**ft_map_s2a(char **arr, char *str, \
						char *(*f)(const char*, const char*))
{
	char	**res;
	int		arr_i;

	res = malloc((ft_arrlen(arr) + 1) * sizeof(char **));
	arr_i = 0;
	while (arr[arr_i] != NULL)
	{
		res[arr_i] = f(arr[arr_i], str);
		if (res[arr_i] == NULL)
		{
			clear_arr(res);
			return (NULL);
		}
		arr_i++;
	}
	res[arr_i] = NULL;
	return (res);
}

void	remove_chars(char *str, char *c)
{
	char	*char_pos;
	int		i;

	i = 0;
	if (str != NULL)
	{
		while (c[i] != '\0')
		{
			char_pos = ft_strchr(str, c[i]);
			while (char_pos != NULL)
			{
				ft_strlcpy(char_pos, char_pos + 1, ft_strlen(char_pos));
				char_pos = ft_strchr(str, c[i]);
			}
			i++;
		}
	}
}

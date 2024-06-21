/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:24:47 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:45:25 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_split_count(const char *s, char deli)
{
	size_t	split_count;
	size_t	iter;
	size_t	s_len;

	s_len = ft_strlen(s);
	split_count = 0;
	iter = 0;
	while (iter <= s_len)
	{
		while (iter <= s_len && s[iter] != deli)
		{
			iter++;
			if (iter <= s_len && (s[iter] == deli || iter == s_len))
				split_count++;
		}
		while (iter <= s_len && s[iter] == deli)
			iter++;
	}
	return (split_count);
}

static size_t	get_limit(const char *s, size_t offset, char deli)
{
	char	*limit;

	limit = ft_strchr((s + offset), deli);
	if (limit == NULL)
		return (ft_strlen(s));
	return ((size_t)(limit - s));
}

static char	*attempt_storage(const char *s, size_t offset, size_t limit)
{
	char	*res;

	res = malloc(limit - offset + 1);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s + offset, (limit - offset + 1));
	return (res);
}

static void	*clear_all(char **res_arr, size_t arr_len)
{
	size_t	count;

	count = 0;
	while (count < arr_len)
	{
		free(res_arr[count]);
		res_arr[count] = NULL;
		count++;
	}
	free(res_arr);
	res_arr = NULL;
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	unsigned int	split_count;
	char			**res_arr;
	size_t			offset;
	size_t			s_len;
	size_t			limit;

	res_arr = malloc(sizeof(char **) * (ft_get_split_count(s, c) + 1));
	if (res_arr == NULL)
		return (NULL);
	offset = 0;
	s_len = ft_strlen(s);
	split_count = 0;
	while (offset < s_len)
	{
		limit = get_limit(s, offset, c);
		if (offset != limit)
		{
			res_arr[split_count] = attempt_storage(s, offset, limit);
			if (res_arr[split_count++] == NULL)
				return (clear_all(res_arr, split_count));
		}
		offset = limit + 1;
	}
	res_arr[split_count] = NULL;
	return (res_arr);
}

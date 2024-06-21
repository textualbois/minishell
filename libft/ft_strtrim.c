/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:35:21 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:44:41 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_rightmost_from_start(const char *str, const char *set)
{
	unsigned int	i;

	i = 0;
	while (i < ft_strlen(str) && ft_strchr(set, str[i]) != NULL)
		i++;
	return (i);
}

static unsigned int	ft_leftmost_from_end(const char *str, const char *set)
{
	unsigned int	i;

	i = ft_strlen(str);
	while (i > 1 && ft_strchr(set, str[i]) != NULL)
		i--;
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char			*res_str;
	unsigned int	start;
	unsigned int	end;

	start = ft_rightmost_from_start(s1, set);
	end = ft_leftmost_from_end(s1, set);
	if (start > end)
	{
		res_str = (char *)malloc(1);
		if (res_str == NULL)
			return (NULL);
		res_str[0] = '\0';
	}
	else
	{
		res_str = (char *)malloc(end - start + 1 + 1 - (ft_strlen(s1) == end));
		if (res_str == NULL)
			return (NULL);
		ft_strlcpy(res_str, s1 + start, end - start + 1 + 1);
	}
	return (res_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:33:09 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:44:50 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	while (i <= len)
	{
		if (ft_strncmp(needle, haystack + i, ft_strlen(needle)) == 0)
		{
			if (i + ft_strlen(needle) <= len)
				return ((char *)(haystack + i));
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

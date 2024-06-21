/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:26:25 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:45:10 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res_str;
	size_t	i;
	size_t	s1len;

	res_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res_str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res_str[i] = s1[i];
		i++;
	}
	s1len = i;
	i = 0;
	while (s2[i] != '\0')
	{
		res_str[s1len + i] = s2[i];
		i++;
	}
	res_str[s1len + i] = '\0';
	return (res_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:45:48 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:44:43 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res_str;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else
	{
		s += start;
		s_len -= start;
	}
	if (s_len < len)
		len = s_len;
	res_str = (char *)malloc(len + 1);
	if (res_str == NULL)
		return (NULL);
	ft_strlcpy(res_str, s, len + 1);
	return (res_str);
}

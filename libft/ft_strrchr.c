/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:35:03 by isemin            #+#    #+#             */
/*   Updated: 2023/10/10 22:31:17 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned int		i;
	char				*last_occurrence;
	size_t				str_len;

	str_len = ft_strlen(str);
	last_occurrence = NULL;
	i = 0;
	while (i <= str_len)
	{
		if (str[i] == (char)c)
			last_occurrence = (char *)(str + i);
		i++;
	}
	return (last_occurrence);
}

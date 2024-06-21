/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:56 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:45:58 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	ptr = (char *) str;
	while (i < n)
	{
		if (ptr[i] == (char)c)
			return ((void *)str + i);
		i++;
	}
	return (NULL);
}

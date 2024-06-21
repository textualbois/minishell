/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:22:45 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:45:51 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t n)
{
	unsigned int	i;
	unsigned char	*dst;
	unsigned char	*src;

	dst = (unsigned char *) dest;
	src = (unsigned char *) source;
	i = n;
	if (dst <= src)
		ft_memcpy(dest, src, n);
	else
	{
		while (i > 0)
		{
			dst[i - 1] = src[i - 1];
			i--;
		}
	}
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:45 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:46:32 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_len(int n)
{
	size_t	size;

	size = (n <= 0);
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	pos;

	pos = int_len(n);
	res = (char *) malloc(pos + 1);
	if (res == NULL)
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(res, (const char *)"-2147483648", pos + 1);
	else if (n == 0)
		ft_strlcpy(res, (const char *)"0", pos + 1);
	else
	{
		n = n - (2 * n * (n < 0));
		res[0] = '-';
		res[pos--] = '\0';
		while (n != 0)
		{
			res[pos--] = (n % 10) + 48;
			n /= 10;
		}
	}
	return (res);
}

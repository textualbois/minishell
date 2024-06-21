/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 20:11:50 by isemin            #+#    #+#             */
/*   Updated: 2024/04/28 19:10:01 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_str_end_wit(const char *s1, const char *s2)
{
	int	len1;
	int	len2;
	int	ptr;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (0);
	ptr = len1 - len2;
	if (ptr < 0)
		return (0);
	while (s1[ptr] != '\0')
	{
		if (s1[ptr] != s2[ptr - (len1 - len2)])
			return (0);
		ptr++;
	}
	if (s2[ptr] == '\0')
		return (1);
	else
		return (0);
}

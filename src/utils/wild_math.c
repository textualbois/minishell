/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_math.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:40:30 by isemin            #+#    #+#             */
/*   Updated: 2024/07/22 15:14:41 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	my_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	my_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

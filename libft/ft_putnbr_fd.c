/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:24:53 by isemin            #+#    #+#             */
/*   Updated: 2023/10/15 21:45:34 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	temp;

	if (n > 9 || n < -9)
	{
		ft_putnbr_fd(n / 10, fd);
		temp = n % 10;
		ft_putchar_fd((temp - (2 * temp * (temp < 0))) + 48, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(-n + 48, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}

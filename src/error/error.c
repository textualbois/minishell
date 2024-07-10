/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:17:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/10 12:06:42 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_error(t_shell *shell, int error_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error_code == 0)
		ft_putstr_fd("error 0\n", STDERR_FILENO);
	else if (error_code == 1)
		ft_putstr_fd("error 1\n", STDERR_FILENO);
	else if (error_code == 2)
		ft_putstr_fd("error 2\n", STDERR_FILENO);
	else if (error_code == 3)
		ft_putstr_fd("error 3\n", STDERR_FILENO);
	else if (error_code == 4)
		ft_putstr_fd("error 4\n", STDERR_FILENO);
	else if (error_code == 5)
		ft_putstr_fd("error 5\n", STDERR_FILENO);
	else if (error_code == 6)
		ft_putstr_fd("error 6\n", STDERR_FILENO);
	//clean(shell);
	(void)shell;
	return (1);
}

int	syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	return (0);
}

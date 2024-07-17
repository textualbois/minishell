/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:18:53 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/17 13:43:52 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_command(t_shell *shell)
{
	(void)shell;
	int		i;

	i = -1;
	while (++i < shell->command_count)
	{
		/* code */
	}
	return (0);
}

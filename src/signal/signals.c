/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:22:29 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/09 12:53:34 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("\b\b \b\b");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGTSTP)
	{
		printf("\nSIGTSTP received\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:22:29 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/22 17:48:42 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

sig_atomic_t	g_sig = 0;

/*
* @ brief: SIGINT (ctrl + c) -> clears the line and displays the prompt.
*/
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 1;
}

/*
* @ brief: SIGQUIT (ctrl + \) -> clears the line and displays the prompt if g=0
* otherwise it sends a SIGQUIT signal to the process and exits.
*/
void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_sig == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		kill(getpid(), SIGQUIT);
		g_sig = 0;
	}
}

/*
* @ brief: Sets up the signal handlers for SIGINT and SIGQUIT.
* can use only 1 sa struct for both signals and just change handler.
*/
void	signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGTSTP, &sa, NULL);
}

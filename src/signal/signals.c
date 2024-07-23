/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:22:29 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/23 15:34:13 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Used as a boolean to show if we are in child process or not
// 0 -> for parent process, 1 -> for child process
volatile sig_atomic_t	g_sig = 0;

/*
* @ brief: SIGINT (ctrl + c) -> clears the line and displays the prompt.
*/
void	handle_sigint(int sig)
{
	(void)sig;
	if (!g_sig)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		write(1, "\n", 1);
		signal(SIGQUIT, SIG_DFL);
		kill(getpid(), SIGQUIT);
	}
}

/*
* @ brief: SIGQUIT (ctrl + \) -> clears the line and displays the prompt if g=0
* otherwise it sends a SIGQUIT signal to the process and exits.
*/
void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_sig)
	{
		write(2, "Process quit\n", 13);
		signal(SIGQUIT, SIG_DFL);
		kill(getpid(), SIGQUIT);
	}
}

/*
* @ brief: SIGQUIT (ctrl + z) -> clears the line and displays the prompt if g=1
* otherwise nothing happens.
*/
void	handle_sigtstp(int sig)
{
	(void)sig;
	if (g_sig)
	{
		write(2, "Process stopped\n", 16);
		signal(SIGTSTP, SIG_DFL);
		kill(getpid(), SIGTSTP);
	}
}

/*
* @ brief: Sets up the signal handlers for SIGINT and SIGQUIT.
* can use only 1 sa struct for both signals and just change handler.
*/
void	setup_signals(void)
{
	struct sigaction	sa;

	set_signal_flag(0);
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = handle_sigtstp;
	sigaction(SIGTSTP, &sa, NULL);
}

// set the bool flag to 0 or 1
// its set to 0 in setupsignals for default and need to be set to 1
// before the child process and after the execution back to 0
void	set_signal_flag(int in_child_process)
{
	g_sig = in_child_process;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:22:29 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/29 19:18:07 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
* @ brief: SIGINT (ctrl + c) -> clears the line and displays the prompt.
* If in_parent_process is FALSE it sends a SIGQUIT signal.
*/
void	handle_sigint(int sig, siginfo_t *siginfo, void *context)
{
	t_shell	*shell;

	(void)sig;
	(void)siginfo;
	shell = (t_shell *)context;
    printf("SIGINT received, is_parent_process = %d\n", shell->is_parent_process);
	if (shell->is_parent_process == true)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (shell->is_parent_process == false)
	{
		write(1, "\n", 1);
		signal(SIGQUIT, SIG_DFL);
		kill(getpid(), SIGQUIT);
	}
}

/*
* @ brief: SIGQUIT (ctrl + \) -> clears the line and displays the prompt if 
*  in_parent_process is FALSE otherwise sends a SIGQUIT signal.
*/
void	handle_sigquit(int sig, siginfo_t *siginfo, void *context)
{
	t_shell	*shell;

	(void)sig;
	(void)siginfo;

	shell = (t_shell *)context;
    printf("SIGINT received, is_parent_process = %d\n", shell->is_parent_process);
	if (shell->is_parent_process == false)
	{
		write(2, "Process quit\n", 13);
		signal(SIGQUIT, SIG_DFL);
		kill(getpid(), SIGQUIT);
	}
}

/*
* @ brief: SIGQUIT (ctrl + z) -> clears the line and displays the prompt if
*  in_parent_process is FALSE otherwise nothing happens.
*/
void	handle_sigtstp(int sig, siginfo_t *siginfo, void *context)
{
	t_shell	*shell;

	(void)sig;
	(void)siginfo;

	shell = (t_shell *)context;
    printf("SIGSTP received, is_parent_process = %d\n", shell->is_parent_process);
	if (shell->is_parent_process == true)
	{
		write(2, "Process stopped\n", 16);
		signal(SIGTSTP, SIG_DFL);
		kill(getpid(), SIGTSTP);
	}
}

/*
* @ brief: Sets up the signal handlers for SIGINT, SIGQUIT and SIGTSTP.
*/
void	setup_signals(t_shell *shell)
{
	struct sigaction	sa;

	(void)shell;
	sa.sa_sigaction = handle_sigint;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_sigaction = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_sigaction = handle_sigtstp;
	sigaction(SIGTSTP, &sa, NULL);
}

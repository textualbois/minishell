/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:22:29 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/02 14:44:28 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
* @ brief: SIGINT (ctrl + c) -> clears the line and displays the prompt.
* If in_parent_process is FALSE it sends a SIGQUIT signal.
*/
void	handle_sigint(t_shell *shell)
{
	if (shell->is_parent_process)
	{
		printf("Parent process handling SIGINT\n");
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("Child process handling SIGINT\n");
		write(1, "\n", 1);
		signal(SIGQUIT, SIG_DFL);
		kill(getpid(), SIGQUIT);
	}
}

/*
* @ brief: SIGQUIT (ctrl + \) -> clears the line and displays the prompt if 
*  in_parent_process is FALSE otherwise sends a SIGQUIT signal.
*/
void	handle_sigquit(t_shell *shell)
{
	if (!shell->is_parent_process)
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
void	handle_sigtstp(t_shell *shell)
{
	if (shell->is_parent_process)
	{
		write(2, "Process stopped\n", 16);
		signal(SIGTSTP, SIG_DFL);
		kill(getpid(), SIGTSTP);
	}
}

/*
 * @brief: General signal handler, stores the signal received in shell.
 */
void	handle_signal(int sig, siginfo_t *siginfo, void *context)
{
	t_shell	*shell;

	shell = (t_shell *)context;
	(void)siginfo;
	shell->sig_received = sig;
}

void	handle_received_signal(t_shell *shell)
{
	if (shell->sig_received != 0)
	{
		if (shell->sig_received == SIGINT)
			handle_sigint(shell);
		else if (shell->sig_received == SIGQUIT)
			handle_sigquit(shell);
		else if (shell->sig_received == SIGTSTP)
			handle_sigtstp(shell);
		shell->sig_received = 0;
	}
}

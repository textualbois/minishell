/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:22:29 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/08 18:21:45 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <readline/readline.h>

// signal handler for sigint ctrl + c
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// signal handler for sigquit ctrl + backslash
void	sigquit_handler(int sig)
{
	(void)sig;
	perror("^\\Quit: 3");
}

// for SIGINT call func. and ignore SIGQUIT
void	signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
* @ brief: Disables the control characters. 
*/
void	disable_ctrl_chars(void)
{
	struct termios	terminal;

	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

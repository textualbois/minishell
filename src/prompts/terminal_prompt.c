/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:48:23 by isemin            #+#    #+#             */
/*   Updated: 2024/07/22 17:51:13 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	disable_ctrl_chars(void)
{
	struct termios	terminal;

	tcgetattr(1, &terminal);
	terminal.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, TCSANOW, &terminal);
}

void	form_prompt(t_shell *shell)
{
	disable_ctrl_chars();
	if (shell->terminal_prompt)
		free(shell->terminal_prompt);
	shell->terminal_prompt = ft_strjoin("$ ", "user :");
}

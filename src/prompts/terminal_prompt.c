/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:48:23 by isemin            #+#    #+#             */
/*   Updated: 2024/08/15 03:12:20 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	form_prompt(t_shell *shell, char *new_user_name)
{
	static char	*user = NULL;
	char		*temp;

	disable_ctrl_chars();
	if (new_user_name)
	{
		if (user)
			free(user);
		user = malloc(sizeof(char) * (ft_strlen(new_user_name) + 1));
		ft_strlcpy(user, new_user_name, ft_strlen(new_user_name) + 1);
	}
	else if (new_user_name == NULL && shell == NULL)
	{
		if (user)
			free(user);
	}
	else
	{
		if (shell->terminal_prompt)
			free(shell->terminal_prompt);
		temp = ft_strjoin("$ ", user);
		shell->terminal_prompt = ft_strjoin(temp, " > ");
		free(temp);
	}
}

void	print_welcome_msg(void)
{
	int		i;
	char	*art[6];

	i = -1;
	art[0] = "╔═══════════════════════════════════════════════╗";
	art[1] = "║ █▀▄▀█ ▀█▀ █▄  █ ▀█▀ █▀▀▀█ █  █ █▀▀▀ █    █    ║";
	art[2] = "║ █ █ █  █  █ █ █  █  ▀▀▀▄▄ █▀▀█ █▀▀▀ █    █    ║";
	art[3] = "║ █   █ ▄█▄ █  ▀█ ▄█▄ █▄▄▄█ █  █ █▄▄▄ █▄▄█ █▄▄█ ║";
	art[4] = "╚═══════════════════════════════════════════════╝";
	art[5] = NULL;
	while (art[++i])
	{
		printf(GREEN"\n%s"RESET, art[i]);
	}
	printf("\n\n");
}

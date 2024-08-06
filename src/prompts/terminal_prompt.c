/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:48:23 by isemin            #+#    #+#             */
/*   Updated: 2024/08/06 14:25:20 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	form_prompt(t_shell *shell, char *new_user_name)
{
	static char	*user = NULL;
	char		*temp;

	if (new_user_name)
	{
		if (user)
			free(user);
		user = malloc(sizeof(char) * (ft_strlen(new_user_name) + 1));
		ft_strlcpy(user, new_user_name, ft_strlen(new_user_name) + 1);
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

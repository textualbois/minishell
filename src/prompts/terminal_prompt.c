/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:48:23 by isemin            #+#    #+#             */
/*   Updated: 2024/07/15 17:47:44 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	form_prompt(t_shell *shell)
{
	if (shell->terminal_prompt)
		free(shell->terminal_prompt);
	shell->terminal_prompt = ft_strjoin("$ ", "user :");
}

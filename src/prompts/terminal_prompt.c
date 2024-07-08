/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:48:23 by isemin            #+#    #+#             */
/*   Updated: 2024/07/08 15:48:19 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	form_prompt(t_shell *shell)
{
	if (shell->terminal_prompt)
		free(shell->terminal_prompt);
	shell->terminal_prompt = ft_strjoin("$ ", "user");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:30:39 by isemin            #+#    #+#             */
/*   Updated: 2024/07/08 13:59:50 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_shell(t_shell *shell, char **env) //should init the shell
{
	if (getenv("USER") == NULL)
	{
		printf("TODO we should get user data on our own in this case\n");
		ft_getenv(); // todo get an environmnet through this. possibly generate some stuff.
	}
	else
	{
		// todo get some stuff from the default env
	}
	// here stuff that need to be done either way
	shell->terminal_prompt = NULL;

}

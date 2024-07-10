/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:43 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/10 13:52:06 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**tokens_to_argv(t_shell *shell)
{
	char	**argv;
	int		i;

	i = -1;
	argv = malloc(sizeof(char *) * (shell->token_count + 1));
	if (!argv)
		return (NULL); //maynw other eror handelign path?
	while (++i < shell->token_count)
	{
		argv[i] = shell->tokens[i].value;
	}
	argv[shell->token_count] = NULL;
	return (argv);
}
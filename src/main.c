/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:43:41 by mrusu             #+#    #+#             */
/*   Updated: 2024/08/09 09:40:31 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		printf(RED"I don't want to argue, no arguments!\n"RESET);
		exit(1);
	}
	init_shell(&shell, env);
	print_welcome_msg();
	shell_loop(&shell);
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:43:41 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/03 17:20:22 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	display_prompt(void)
{
	printf(GREEN "minishell> " RESET);
}

char	*read_input(void)
{
	char	*line;
	size_t	bufsize;

	line = NULL;
	bufsize = 0;
	getline(&line, &bufsize, stdin);
	return (line);
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

int	loop(void)
{
	char	*input;

	display_prompt();
	input = read_input();
	if (!input)
	{
		printf("\nExiting minishell. Goodbye!\n");
		return (0);
	}
	free(input);
	return (1);
}

int	main(int ac, char *av[], char *env[])
{
//	t_data	data;

	if (ac != 1 || av[1])
	{
		printf(RED"I don't want to argue, no arguments!\n"RESET);
		exit(1);
	}
	//init_data(&data, env);
	print_welcome_msg();
	while (loop())
		;
	(void)ac;
	(void)av;
	(void)env;
	return (0);
}

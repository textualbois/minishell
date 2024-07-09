/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:13 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/09 15:33:16 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

// own lib's
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include "structures.h"

// Colors
# define RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define WHITE "\033[0;37m"
# define RESET "\033[m"

// Typdef



// **********************====FUNCTION DECLARATION====*********************
// main.c

//loop
//loop.c
int		shell_loop(t_shell	*shell);
void	*ft_readline(t_shell *shell);

// setup
// init_shell.c
void	init_shell(t_shell *shell, char **env);

// env.c
char	*ft_getenv(void);

// prompts
// terminal_prompt.c
void	form_prompt(t_shell *shell);

// utile
// ---utiles0.c
char	**ft_arrdup(char **arr);

// error.c
int		ft_error(t_data *data, int error_code);
int		syntax_error(void);

void	display_prompt(void);
char	*read_input(void);
void	print_welcome_msg(void);
int		loop(t_data *data);



// lexer.c


//parse.c

#endif